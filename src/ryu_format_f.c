/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:21 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/26 14:18:23 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

int		ft_format_int_without_exp(t_decomposed_dbl d,
									char *const s, int ix)
{
	int			non_zero;
	int32_t		i;
	uint32_t	x;
	uint32_t	digits;

	non_zero = 0;
	if (d.e >= -52)
	{
		x = d.e < 0 ? 0 : IX4EXP((uint32_t)d.e);
		i = (int32_t)LEN4IX(x);
		while (--i >= 0)
		{
			digits = ft_mul_shift_mod1e9(d.m << 8,
				g_pow10_split[g_pow10_offset[x] + i],
				(int32_t)((POW10_BITS4IX(x) - d.e) + 8));
			if (non_zero)
				ix = ft_append_nine_digits(digits, s, ix);
			else if (digits != 0)
			{
				ix = ft_append_n_digits(ft_decimal_len9(digits), digits, s, ix);
				non_zero = 1;
			}
		}
	}
	if (!non_zero)
		s[ix++] = '0';
	return (ix);
}

char	*ft_format_f(t_decomposed_dbl d, t_float_format_options *opts,
					char *const result, int index)
{
	index = ft_format_int_without_exp(d, result, index);
	if (opts->precision > 0 || opts->flags & FLAG_ALTERNATIVE_FORM)
		result[index++] = '.';
	if (d.e < 0)
	{
		const int32_t idx = -d.e / 16;
		const uint32_t blocks = opts->precision / 9 + 1;
		// 0 = don't round up; 1 = round up unconditionally; 2 = round up if odd.
		int roundUp = 0;
		uint32_t i = 0;
		if (blocks <= g_min_block_2[idx])
		{
			i = blocks;
			ft_memset(result + index, '0', opts->precision);
			index += opts->precision;
		}
		else if (i < g_min_block_2[idx])
		{
			i = g_min_block_2[idx];
			ft_memset(result + index, '0', 9 * i);
			index += 9 * i;
		}
		for (; i < blocks; ++i)
		{
			const uint32_t p = g_pow10_offset_2[idx] + i - g_min_block_2[idx];
			if (p >= g_pow10_offset_2[idx + 1])
			{
				// If the remaining digits are all 0, then we might as well use ft_memset.
				// No rounding required in this case.
				const uint32_t fill = opts->precision - 9 * i;
				ft_memset(result + index, '0', fill);
				index += fill;
				break ;
			}
			uint32_t digits = ft_mul_shift_mod1e9(
					d.m << 8,
					g_pow10_split_2[p],
					ADDITIONAL_BITS_2 + (-d.e - 16 * idx) + 8
			);
			if (i < blocks - 1)
				index = ft_append_nine_digits(digits, result, index);
			else
			{
				const uint32_t maximum = opts->precision - 9 * i;
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
					// Is mmmm * 10^(additionalDigits + 1) / 2^(-d.e) integer?
					const int32_t requiredTwos = -d.e - (int32_t)opts->precision - 1;
					const int trailingZeros = requiredTwos <= 0
						|| (requiredTwos < 60 && IS_DIV_POW2(d.m, (uint32_t)requiredTwos));
					roundUp = trailingZeros ? 2 : 1;
				}
				if (maximum > 0)
					index = ft_append_c_digits(maximum, digits, result, index);
				break ;
			}
		}
		if (roundUp != 0)
		{
			int roundIndex = index;
			int dotIndex = 0; // '.' can't be located at index 0
			while (1)
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
		ft_memset(result + index, '0', opts->precision);
		index += opts->precision;
	}
	return (result);
}
