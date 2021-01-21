#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ryu.h"
#include "ryu_cache.h"

/*
** Convert `digits` to a sequence of decimal digits. Append the digits to the
** result. The caller has to guarantee that:
**
**   10^(olen-1) <= digits < 10^olen
**
** e.g., by passing `olen` as `ft_decimal_len9(digits)`.
*/

static inline void		append_n_digits(const uint32_t olen,
									uint32_t digits, char* const result)
{
	uint32_t i;
	uint32_t c;

	i = 0;
	while (digits >= 10000)
	{
		c = MOD(digits, 10000);
		digits /= 10000;
		ft_memcpy(result + olen - i - 2, g_digit_tab + ((c % 100) << 1), 2);
		ft_memcpy(result + olen - i - 4, g_digit_tab + ((c / 100) << 1), 2);
		i += 4;
	}
	if (digits >= 100)
	{
		c = (digits % 100) << 1;
		digits /= 100;
		ft_memcpy(result + olen - i - 2, g_digit_tab + c, 2);
		i += 2;
	}
	if (digits >= 10)
		ft_memcpy(result + olen - i - 2, g_digit_tab + (digits << 1), 2);
	else
		result[0] = (char)('0' + digits);
}

/*
** Convert `digits` to a sequence of decimal digits. Print the first digit,
** followed by a decimal dot '.' followed by the remaining digits. The caller
** has to guarantee that:
**
**   10^(olen-1) <= digits < 10^olen
**
** e.g., by passing `olen` as `ft_decimal_len9(digits)`.
*/

static inline void		append_d_digits(const uint32_t olen, uint32_t digits,
									char* const result)
{
	uint32_t i;
	uint32_t c;

	i = 0;
	while (digits >= 10000)
	{
		c = MOD(digits, 10000);
		digits /= 10000;
		ft_memcpy(result + olen + 1 - i - 2, g_digit_tab + ((c % 100) << 1), 2);
		ft_memcpy(result + olen + 1 - i - 4, g_digit_tab + ((c / 100) << 1), 2);
		i += 4;
	}
	if (digits >= 100)
	{
		c = ((digits % 100) << 1);
		digits /= 100;
		ft_memcpy(result + olen + 1 - i - 2, g_digit_tab + c, 2);
		i += 2;
	}
	if (digits >= 10)
	{
		c = digits << 1;
		result[2] = g_digit_tab[c + 1];
		result[1] = '.';
		result[0] = g_digit_tab[c];
	}
	else
	{
		result[1] = '.';
		result[0] = (char)('0' + digits);
	}
}

/*
** Convert `digits` to decimal and write the last `count` decimal digits to
** result. If `digits` contains additional digits, then those are silently
** ignored.
*/

static inline void		append_c_digits(const uint32_t count, uint32_t digits,
									char* const result)
{
	// Copy pairs of digits from g_digit_tab.
	uint32_t i = 0;
	for (; i < count - 1; i += 2)
	{
		const uint32_t c = (digits % 100) << 1;
		digits /= 100;
		ft_memcpy(result + count - i - 2, g_digit_tab + c, 2);
	}
	// Generate the last digit if count is odd.
	if (i < count)
	{
		const char c = (char)('0' + (digits % 10));
		result[count - i - 1] = c;
	}
}

/*
** Convert `digits` to decimal and write the last 9 decimal digits to result.
** If `digits` contains additional digits, then those are silently ignored.
*/

static inline void		append_nine_digits(uint32_t digits, char* const result)
{
	if (digits == 0)
	{
		memset(result, '0', 9);
		return ;
	}
	for (uint32_t i = 0; i < 5; i += 4)
	{
		const uint32_t c = MOD(digits, 10000);
		digits /= 10000;
		const uint32_t c0 = (c % 100) << 1;
		const uint32_t c1 = (c / 100) << 1;
		ft_memcpy(result + 7 - i, g_digit_tab + c0, 2);
		ft_memcpy(result + 5 - i, g_digit_tab + c1, 2);
	}
	result[0] = (char)('0' + digits);
}

static inline int		copy_special_str_printf(char* const result,
									const bool sign, const uint64_t mantissa)
{
	if (mantissa)
	{
		ft_memcpy(result, "nan", 3);
		return (3);
	}
	if (sign)
		result[0] = '-';
	ft_memcpy(result + sign, "Infinity", 8);
	return (sign + 8);
}

int						d2fixed_buffered_n(double d, uint32_t precision,
											char* result)
{
	const uint64_t bits = ft_double_to_bits(d);
	// Decode bits into sign, mantissa, and exponent.
	const bool ieeeSign = ((bits >> (DOUBLE_MANTISSA_BITS + DOUBLE_EXPONENT_BITS)) & 1) != 0;
	const uint64_t ieeeMantissa = bits & ((1ull << DOUBLE_MANTISSA_BITS) - 1);
	const uint32_t ieeeExponent = (uint32_t)((bits >> DOUBLE_MANTISSA_BITS) & ((1u << DOUBLE_EXPONENT_BITS) - 1));

	// Case distinction; exit early for the easy cases.
	if (ieeeExponent == ((1u << DOUBLE_EXPONENT_BITS) - 1u))
		return (copy_special_str_printf(result, ieeeSign, ieeeMantissa));
	if (ieeeExponent == 0 && ieeeMantissa == 0)
	{
		int index = 0;
		if (ieeeSign)
			result[index++] = '-';
		result[index++] = '0';
		if (precision > 0)
		{
			result[index++] = '.';
			memset(result + index, '0', precision);
			index += precision;
		}
		return (index);
	}

	int32_t e2;
	uint64_t m2;
	if (ieeeExponent == 0)
	{
		e2 = 1 - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;
		m2 = ieeeMantissa;
	}
	else
	{
		e2 = (int32_t)ieeeExponent - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;
		m2 = (1ull << DOUBLE_MANTISSA_BITS) | ieeeMantissa;
	}

	int index = 0;
	bool nonzero = false;
	if (ieeeSign)
		result[index++] = '-';
	if (e2 >= -52)
	{
		const uint32_t idx = e2 < 0 ? 0 : IX4EXP((uint32_t)e2);
		const uint32_t p10bits = POW10_BITS4IX(idx);
		const int32_t len = (int32_t)LEN4IX(idx);
		for (int32_t i = len - 1; i >= 0; --i)
		{
			const uint32_t j = p10bits - e2;
			// Temporary: j is usually around 128, and by shifting a bit, we push
			// it to 128 or above, which is a slightly faster code path
			// in ft_mul_shift_mod1e9. Instead, we can just increase the multipliers.
			const uint32_t digits = ft_mul_shift_mod1e9(m2 << 8, g_pow10_split[g_pow10_offset[idx] + i], (int32_t)(j + 8));
			if (nonzero)
			{
				append_nine_digits(digits, result + index);
				index += 9;
			}
			else if (digits != 0)
			{
				const uint32_t olen = ft_decimal_len9(digits);
				append_n_digits(olen, digits, result + index);
				index += olen;
				nonzero = true;
			}
		}
	}
	if (!nonzero)
		result[index++] = '0';
	if (precision > 0)
		result[index++] = '.';
	if (e2 < 0)
	{
		const int32_t idx = -e2 / 16;
		const uint32_t blocks = precision / 9 + 1;
		// 0 = don't round up; 1 = round up unconditionally; 2 = round up if odd.
		int roundUp = 0;
		uint32_t i = 0;
		if (blocks <= g_min_block_2[idx])
		{
			i = blocks;
			memset(result + index, '0', precision);
			index += precision;
		}
		else if (i < g_min_block_2[idx])
		{
			i = g_min_block_2[idx];
			memset(result + index, '0', 9 * i);
			index += 9 * i;
		}
		for (; i < blocks; ++i)
		{
			const int32_t j = ADDITIONAL_BITS_2 + (-e2 - 16 * idx);
			const uint32_t p = g_pow10_offset_2[idx] + i - g_min_block_2[idx];
			if (p >= g_pow10_offset_2[idx + 1])
			{
				// If the remaining digits are all 0, then we might as well use memset.
				// No rounding required in this case.
				const uint32_t fill = precision - 9 * i;
				memset(result + index, '0', fill);
				index += fill;
				break ;
			}
			// Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
			// a slightly faster code path in ft_mul_shift_mod1e9. Instead, we can just increase the multipliers.
			uint32_t digits = ft_mul_shift_mod1e9(m2 << 8, g_pow10_split_2[p], j + 8);
			if (i < blocks - 1)
			{
				append_nine_digits(digits, result + index);
				index += 9;
			}
			else
			{
				const uint32_t maximum = precision - 9 * i;
				uint32_t lastDigit = 0;
				for (uint32_t k = 0; k < 9 - maximum; ++k)
				{
					lastDigit = digits % 10;
					digits /= 10;
				}
				if (lastDigit != 5)
					roundUp = lastDigit > 5;
				else
				{
					// Is m * 10^(additionalDigits + 1) / 2^(-e2) integer?
					const int32_t requiredTwos = -e2 - (int32_t)precision - 1;
					const bool trailingZeros = requiredTwos <= 0
						|| (requiredTwos < 60 && IS_DIV_POW2(m2, (uint32_t)requiredTwos));
					roundUp = trailingZeros ? 2 : 1;
				}
				if (maximum > 0)
				{
					append_c_digits(maximum, digits, result + index);
					index += maximum;
				}
				break ;
			}
		}
		if (roundUp != 0)
		{
			int roundIndex = index;
			int dotIndex = 0; // '.' can't be located at index 0
			while (true)
			{
				--roundIndex;
				char c;
				if (roundIndex == -1 || (c = result[roundIndex], c == '-'))
				{
					result[roundIndex + 1] = '1';
					if (dotIndex > 0)
					{
						result[dotIndex] = '0';
						result[dotIndex + 1] = '.';
					}
					result[index++] = '0';
					break ;
				}
				if (c == '.')
				{
					dotIndex = roundIndex;
					continue ;
				}
				else if (c == '9')
				{
					result[roundIndex] = '0';
					roundUp = 1;
					continue ;
				}
				else
				{
					if (roundUp == 2 && c % 2 == 0)
						break ;
					result[roundIndex] = c + 1;
					break ;
				}
			}
		}
	}
	else
	{
		memset(result + index, '0', precision);
		index += precision;
	}
	return (index);
}

void				d2fixed_buffered(double d, uint32_t precision, char* result)
{
	const int len = d2fixed_buffered_n(d, precision, result);
	result[len] = '\0';
}

char				*d2fixed(double d, uint32_t precision)
{
	char* const buffer = (char*)malloc(2000);
	const int index = d2fixed_buffered_n(d, precision, buffer);
	buffer[index] = '\0';
	return (buffer);
}

int d2exp_buffered_n(double d, uint32_t precision, char* result)
{
	const uint64_t bits = ft_double_to_bits(d);

	// Decode bits into sign, mantissa, and exponent.
	const bool ieeeSign = ((bits >> (DOUBLE_MANTISSA_BITS + DOUBLE_EXPONENT_BITS)) & 1) != 0;
	const uint64_t ieeeMantissa = bits & ((1ull << DOUBLE_MANTISSA_BITS) - 1);
	const uint32_t ieeeExponent = (uint32_t)((bits >> DOUBLE_MANTISSA_BITS) & ((1u << DOUBLE_EXPONENT_BITS) - 1));

	// Case distinction; exit early for the easy cases.
	if (ieeeExponent == ((1u << DOUBLE_EXPONENT_BITS) - 1u))
		return (copy_special_str_printf(result, ieeeSign, ieeeMantissa));
	if (ieeeExponent == 0 && ieeeMantissa == 0)
	{
		int index = 0;
		if (ieeeSign)
			result[index++] = '-';
		result[index++] = '0';
		if (precision > 0)
		{
			result[index++] = '.';
			memset(result + index, '0', precision);
			index += precision;
		}
		ft_memcpy(result + index, "e+00", 4);
		index += 4;
		return (index);
	}

	int32_t e2;
	uint64_t m2;
	if (ieeeExponent == 0)
	{
		e2 = 1 - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;
		m2 = ieeeMantissa;
	}
	else
	{
		e2 = (int32_t)ieeeExponent - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;
		m2 = (1ull << DOUBLE_MANTISSA_BITS) | ieeeMantissa;
	}

	const bool printDecimalPoint = precision > 0;
	++precision;
	int index = 0;
	if (ieeeSign)
		result[index++] = '-';
	uint32_t digits = 0;
	uint32_t printedDigits = 0;
	uint32_t availableDigits = 0;
	int32_t exp = 0;
	if (e2 >= -52)
	{
		const uint32_t idx = e2 < 0 ? 0 : IX4EXP((uint32_t)e2);
		const uint32_t p10bits = POW10_BITS4IX(idx);
		const int32_t len = (int32_t)LEN4IX(idx);
		for (int32_t i = len - 1; i >= 0; --i)
		{
			const uint32_t j = p10bits - e2;
			// Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
			// a slightly faster code path in ft_mul_shift_mod1e9. Instead, we can just increase the multipliers.
			digits = ft_mul_shift_mod1e9(m2 << 8, g_pow10_split[g_pow10_offset[idx] + i], (int32_t)(j + 8));
			if (printedDigits != 0)
			{
				if (printedDigits + 9 > precision)
				{
					availableDigits = 9;
					break ;
				}
				append_nine_digits(digits, result + index);
				index += 9;
				printedDigits += 9;
			}
			else if (digits != 0)
			{
				availableDigits = ft_decimal_len9(digits);
				exp = i * 9 + (int32_t)availableDigits - 1;
				if (availableDigits > precision)
					break ;
				if (printDecimalPoint)
				{
					append_d_digits(availableDigits, digits, result + index);
					index += availableDigits + 1; // +1 for decimal point
				}
				else
					result[index++] = (char)('0' + digits);
				printedDigits = availableDigits;
				availableDigits = 0;
			}
		}
	}

	if (e2 < 0 && availableDigits == 0)
	{
		const int32_t idx = -e2 / 16;
		for (int32_t i = g_min_block_2[idx]; i < 200; ++i)
		{
			const int32_t j = ADDITIONAL_BITS_2 + (-e2 - 16 * idx);
			const uint32_t p = g_pow10_offset_2[idx] + (uint32_t)i - g_min_block_2[idx];
			// Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
			// a slightly faster code path in ft_mul_shift_mod1e9. Instead, we can just increase the multipliers.
			digits = (p >= g_pow10_offset_2[idx + 1]) ? 0 : ft_mul_shift_mod1e9(m2 << 8, g_pow10_split_2[p], j + 8);
			if (printedDigits != 0)
			{
				if (printedDigits + 9 > precision)
				{
					availableDigits = 9;
					break ;
				}
				append_nine_digits(digits, result + index);
				index += 9;
				printedDigits += 9;
			}
			else if (digits != 0)
			{
				availableDigits = ft_decimal_len9(digits);
				exp = -(i + 1) * 9 + (int32_t)availableDigits - 1;
				if (availableDigits > precision)
					break ;
				if (printDecimalPoint)
				{
					append_d_digits(availableDigits, digits, result + index);
					index += availableDigits + 1; // +1 for decimal point
				}
				else
					result[index++] = (char)('0' + digits);
				printedDigits = availableDigits;
				availableDigits = 0;
			}
		}
	}

	const uint32_t maximum = precision - printedDigits;
	if (availableDigits == 0)
		digits = 0;
	uint32_t lastDigit = 0;
	if (availableDigits > maximum)
	{
		for (uint32_t k = 0; k < availableDigits - maximum; ++k)
		{
			lastDigit = digits % 10;
			digits /= 10;
		}
	}
	// 0 = don't round up; 1 = round up unconditionally; 2 = round up if odd.
	int roundUp = 0;
	if (lastDigit != 5)
		roundUp = lastDigit > 5;
	else
	{
		// Is m * 2^e2 * 10^(precision + 1 - exp) integer?
		// precision was already increased by 1, so we don't need to write + 1 here.
		const int32_t rexp = (int32_t)precision - exp;
		const int32_t requiredTwos = -e2 - rexp;
		bool trailingZeros = requiredTwos <= 0
			|| (requiredTwos < 60 && IS_DIV_POW2(m2, (uint32_t)requiredTwos));
		if (rexp < 0)
		{
			const int32_t requiredFives = -rexp;
			trailingZeros = trailingZeros && ft_is_div_pow5(m2, requiredFives);
		}
		roundUp = trailingZeros ? 2 : 1;
	}
	if (printedDigits != 0)
	{
		if (digits == 0)
			memset(result + index, '0', maximum);
		else
			append_c_digits(maximum, digits, result + index);
		index += maximum;
	}
	else
	{
		if (printDecimalPoint)
		{
			append_d_digits(maximum, digits, result + index);
			index += maximum + 1; // +1 for decimal point
		}
		else
			result[index++] = (char)('0' + digits);
	}
	if (roundUp != 0)
	{
		int roundIndex = index;
		while (true)
		{
			--roundIndex;
			char c;
			if (roundIndex == -1 || (c = result[roundIndex], c == '-'))
			{
				result[roundIndex + 1] = '1';
				++exp;
				break ;
			}
			if (c == '.')
				continue ;
			else if (c == '9')
			{
				result[roundIndex] = '0';
				roundUp = 1;
				continue ;
			}
			else
			{
				if (roundUp == 2 && c % 2 == 0)
					break ;
				result[roundIndex] = c + 1;
				break ;
			}
		}
	}
	result[index++] = 'e';
	if (exp < 0)
	{
		result[index++] = '-';
		exp = -exp;
	}
	else
		result[index++] = '+';

	if (exp >= 100)
	{
		const int32_t c = exp % 10;
		ft_memcpy(result + index, g_digit_tab + 2 * (exp / 10), 2);
		result[index + 2] = (char)('0' + c);
		index += 3;
	}
	else
	{
		ft_memcpy(result + index, g_digit_tab + 2 * exp, 2);
		index += 2;
	}

	return (index);
}

void					d2exp_buffered(double d, uint32_t precision,
										char* result)
{
	const int len = d2exp_buffered_n(d, precision, result);
	result[len] = '\0';
}

char					*d2exp(double d, uint32_t precision)
{
	char *const buffer = (char *)malloc(2000);
	const int index = d2exp_buffered_n(d, precision, buffer);
	buffer[index] = '\0';
	return (buffer);
}
