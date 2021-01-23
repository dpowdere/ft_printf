/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_dtoa_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:31:20 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:31:27 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "libftprintf.h"

int		ft_dtoa_e(double d, char *result, uint32_t precision, int use_uppercase)
{
	const uint64_t bits = *(uint64_t *)&d;
	const int ieeeSign = ((bits >> (DBL_MANTISSA_BITS + DBL_EXPONENT_BITS)) & 1) != 0;
	const uint64_t ieeeMantissa = bits & ((1ull << DBL_MANTISSA_BITS) - 1);
	const uint32_t ieeeExponent = (uint32_t)((bits >> DBL_MANTISSA_BITS) & ((1u << DBL_EXPONENT_BITS) - 1));
	int index = 0;

	if (ieeeExponent == ((1u << DBL_EXPONENT_BITS) - 1u))
		return (ft_copy_special_str_printf(result,
					ieeeSign, ieeeMantissa, use_uppercase));
	if (ieeeExponent == 0 && ieeeMantissa == 0)
	{
		if (ieeeSign)
			result[index++] = '-';
		result[index++] = '0';
		if (precision > 0)
		{
			result[index++] = '.';
			ft_memset(result + index, '0', precision);
			index += precision;
		}
		ft_memcpy(result + index, "e+00", 4);
		index += 4;
		return (index);
	}
	if (ieeeSign)
		result[index++] = '-';

	int32_t e2;
	uint64_t m2;
	if (ieeeExponent == 0)
	{
		e2 = 1 - DBL_BIAS - DBL_MANTISSA_BITS;
		m2 = ieeeMantissa;
	}
	else
	{
		e2 = (int32_t)ieeeExponent - DBL_BIAS - DBL_MANTISSA_BITS;
		m2 = (1ull << DBL_MANTISSA_BITS) | ieeeMantissa;
	}

	const int printDecimalPoint = precision > 0;
	++precision;
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
				ft_append_nine_digits(digits, result + index);
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
					ft_append_d_digits(availableDigits, digits, result + index);
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
				ft_append_nine_digits(digits, result + index);
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
					ft_append_d_digits(availableDigits, digits, result + index);
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
		int trailingZeros = requiredTwos <= 0
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
			ft_memset(result + index, '0', maximum);
		else
			ft_append_c_digits(maximum, digits, result + index);
		index += maximum;
	}
	else
	{
		if (printDecimalPoint)
		{
			ft_append_d_digits(maximum, digits, result + index);
			index += maximum + 1; // +1 for decimal point
		}
		else
			result[index++] = (char)('0' + digits);
	}
	if (roundUp != 0)
	{
		int roundIndex = index;
		while (1)
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
