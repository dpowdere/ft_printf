/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:44 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/31 19:57:55 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

int		ft_format_exp(int32_t exp, t_float_format_options *opts,
						char *const result, int index)
{
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
	return (index);
}

char	*ft_format_e(t_decomposed_dbl d, char *const result, int index)
{
	++d.opts->precision;

	uint32_t digits = 0;
	uint32_t printed_digits = 0;
	uint32_t available_digits = 0;
	int32_t exp = 0;
	if (d.e >= -52)
	{
		const uint32_t idx = d.e < 0 ? 0 : IX4EXP((uint32_t)d.e);
		const uint32_t p10bits = POW10_BITS4IX(idx);
		const int32_t len = (int32_t)LEN4IX(idx);
		for (int32_t i = len - 1; i >= 0; --i)
		{
			digits = ft_mul_shift_mod1e9(
				d.m << 8,
				g_pow10_split[g_pow10_offset[idx] + i],
				(int32_t)((p10bits - d.e) + 8));
			if (printed_digits != 0)
			{
				if (printed_digits + 9 > (uint32_t)d.opts->precision)
				{
					available_digits = 9;
					break ;
				}
				index = ft_append_nine_digits(digits, result, index);
				printed_digits += 9;
			}
			else if (digits != 0)
			{
				available_digits = ft_decimal_len9(digits);
				exp = i * 9 + (int32_t)available_digits - 1;
				if (available_digits > (uint32_t)d.opts->precision)
					break ;
				if (d.show_dot)
					index = ft_append_d_digits(available_digits, digits, result, index);
				else
					result[index++] = (char)('0' + digits);
				printed_digits = available_digits;
				available_digits = 0;
			}
		}
	}

	if (d.e < 0 && available_digits == 0)
	{
		const int32_t idx = -d.e / 16;
		for (int32_t i = g_min_block_2[idx]; i < 200; ++i)
		{
			const uint32_t p = g_pow10_offset_2[idx] + (uint32_t)i - g_min_block_2[idx];
			digits = (p >= g_pow10_offset_2[idx + 1])
				? 0
				: ft_mul_shift_mod1e9(
					d.m << 8,
					g_pow10_split_2[p],
					ADDITIONAL_BITS_2 + (-d.e - 16 * idx) + 8
				);
			if (printed_digits != 0)
			{
				if (printed_digits + 9 > (uint32_t)d.opts->precision)
				{
					available_digits = 9;
					break ;
				}
				index = ft_append_nine_digits(digits, result, index);
				printed_digits += 9;
			}
			else if (digits != 0)
			{
				available_digits = ft_decimal_len9(digits);
				exp = -(i + 1) * 9 + (int32_t)available_digits - 1;
				if (available_digits > (uint32_t)d.opts->precision)
					break ;
				if (d.show_dot)
					index = ft_append_d_digits(available_digits, digits, result, index);
				else
					result[index++] = (char)('0' + digits);
				printed_digits = available_digits;
				available_digits = 0;
			}
		}
	}

	const uint32_t maximum = d.opts->precision - printed_digits;
	if (available_digits == 0)
		digits = 0;
	uint32_t last_digit = 0;
	if (available_digits > maximum)
	{
		for (uint32_t k = 0; k < available_digits - maximum; ++k)
		{
			last_digit = digits % 10;
			digits /= 10;
		}
	}

	if (last_digit != 5)
		d.roundup = last_digit > 5 ? ROUNDUP_UNCONDITIONALLY : ROUNDUP_NEVER;
	else
	{
		// Is m * 2^d.e * 10^(precision + 1 - exp) integer?
		// precision was already increased by 1, so we don't need to write + 1 here.
		const int32_t rexp = (int32_t)d.opts->precision - exp;
		const int32_t required_twos = -d.e - rexp;
		int trailing_zeros = required_twos <= 0
			|| (required_twos < 60 && IS_DIV_POW2(d.m, (uint32_t)required_twos));
		if (rexp < 0)
		{
			const int32_t required_fives = -rexp;
			trailing_zeros = trailing_zeros && ft_is_div_pow5(d.m, required_fives);
		}
		d.roundup = trailing_zeros ? ROUNDUP_IF_ODD : ROUNDUP_UNCONDITIONALLY;
	}
	if (printed_digits != 0)
		index = ft_append_c_digits(maximum, digits, result, index);
	else
	{
		if (d.show_dot)
			index = ft_append_d_digits(maximum, digits, result, index);
		else
			result[index++] = (char)('0' + digits);
	}
	if (d.roundup != ROUNDUP_NEVER)
	{
		int round_index = index;
		while (1)
		{
			--round_index;
			char c;
			if (round_index == -1 || ((c = result[round_index]) == '-'))
			{
				result[round_index + 1] = '1';
				++exp;
				break ;
			}
			if (c == '.')
				continue ;
			else if (c == '9')
			{
				result[round_index] = '0';
				d.roundup = ROUNDUP_UNCONDITIONALLY;
				continue ;
			}
			else
			{
				if (d.roundup == ROUNDUP_IF_ODD && c % 2 == 0)
					break ;
				result[round_index] = c + 1;
				break ;
			}
		}
	}

	index = ft_format_exp(exp, d.opts, result, index);
	return (result);
}
