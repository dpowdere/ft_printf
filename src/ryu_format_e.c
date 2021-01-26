/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:44 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/26 14:18:45 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

char	*ft_format_e(t_decomposed_dbl d,
					t_float_format_options *opts, char *result, int index)
{
	const int printDecimalPoint = opts->precision > 0 || opts->flags & FLAG_ALTERNATIVE_FORM;
	++opts->precision;
	uint32_t digits = 0;
	uint32_t printedDigits = 0;
	uint32_t availableDigits = 0;
	int32_t exp = 0;
	if (d.e >= -52)
	{
		const uint32_t idx = d.e < 0 ? 0 : IX4EXP((uint32_t)d.e);
		const uint32_t p10bits = POW10_BITS4IX(idx);
		const int32_t len = (int32_t)LEN4IX(idx);
		for (int32_t i = len - 1; i >= 0; --i)
		{
			const uint32_t j = p10bits - d.e;
			// Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
			// a slightly faster code path in ft_mul_shift_mod1e9. Instead, we can just increase the multipliers.
			digits = ft_mul_shift_mod1e9(d.m << 8, g_pow10_split[g_pow10_offset[idx] + i], (int32_t)(j + 8));
			if (printedDigits != 0)
			{
				if (printedDigits + 9 > (uint32_t)opts->precision)
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
				if (availableDigits > (uint32_t)opts->precision)
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

	if (d.e < 0 && availableDigits == 0)
	{
		const int32_t idx = -d.e / 16;
		for (int32_t i = g_min_block_2[idx]; i < 200; ++i)
		{
			const int32_t j = ADDITIONAL_BITS_2 + (-d.e - 16 * idx);
			const uint32_t p = g_pow10_offset_2[idx] + (uint32_t)i - g_min_block_2[idx];
			// Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
			// a slightly faster code path in ft_mul_shift_mod1e9. Instead, we can just increase the multipliers.
			digits = (p >= g_pow10_offset_2[idx + 1]) ? 0 : ft_mul_shift_mod1e9(d.m << 8, g_pow10_split_2[p], j + 8);
			if (printedDigits != 0)
			{
				if (printedDigits + 9 > (uint32_t)opts->precision)
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
				if (availableDigits > (uint32_t)opts->precision)
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

	const uint32_t maximum = opts->precision - printedDigits;
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
		// Is mmmm * 2^d.e * 10^(precision + 1 - exp) integer?
		// precision was already increased by 1, so we don't need to write + 1 here.
		const int32_t rexp = (int32_t)opts->precision - exp;
		const int32_t requiredTwos = -d.e - rexp;
		int trailingZeros = requiredTwos <= 0
			|| (requiredTwos < 60 && IS_DIV_POW2(d.m, (uint32_t)requiredTwos));
		if (rexp < 0)
		{
			const int32_t requiredFives = -rexp;
			trailingZeros = trailingZeros && ft_is_div_pow5(d.m, requiredFives);
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
	if (opts->flags & FLAG_USE_UPPERCASE)
		result[index++] = *FLT_EXP_UPPER;
	else
		result[index++] = *FLT_EXP_LOWER;
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

	return (result);
}