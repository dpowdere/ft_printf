/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:21 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/27 00:20:30 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

char					*ft_format_f(t_decomposed_dbl d,
										t_float_format_options *opts,
										char *const result, int index)
{
	index = ft_format_int_without_exp(d, result, index);
	if (opts->precision > 0 || opts->flags & FLAG_ALTERNATIVE_FORM)
		result[index++] = '.';
	if (d.e < 0)
	{


		int32_t		tab_index;
		uint32_t	blocks;
		uint32_t	i;
		t_roundup	roundup;

		tab_index = -d.e / 16;
		blocks = opts->precision / 9 + 1;
		roundup = ROUNDUP_NONE;
		i = 0;
		if (blocks <= g_min_block_2[tab_index])
		{
			i = blocks;
			ft_memset(result + index, '0', opts->precision);
			index += opts->precision;
		}
		else if (i < g_min_block_2[tab_index])
		{
			i = g_min_block_2[tab_index];
			ft_memset(result + index, '0', 9 * i);
			index += 9 * i;
		}
		while (i < blocks)
		{
			const uint32_t p = g_pow10_offset_2[tab_index] + i - g_min_block_2[tab_index];
			if (p >= g_pow10_offset_2[tab_index + 1])
			{
				const uint32_t fill = opts->precision - 9 * i;
				ft_memset(result + index, '0', fill);
				index += fill;
				break ;
			}

			uint32_t digits = ft_mul_shift_mod1e9(
					d.m << 8,
					g_pow10_split_2[p],
					ADDITIONAL_BITS_2 + (-d.e - 16 * tab_index) + 8
			);
			if (i < blocks - 1)
				index = ft_append_nine_digits(digits, result, index);
			else
			{
				const uint32_t maximum = opts->precision - 9 * i;
				uint32_t last_digit = 0;
				uint32_t k = 0;
				while (k++ < 9 - maximum)
				{
					last_digit = digits % 10;
					digits /= 10;
				}
				if (last_digit != 5)
					roundup = last_digit > 5 ? ROUNDUP_UNCONDITIONALLY : ROUNDUP_NONE;
				else
				{
					// Is m * 10^(additionalDigits + 1) / 2^(-d.e) integer?
					const int32_t required_twos = -d.e - (int32_t)opts->precision - 1;
					const int trailing_zeros = required_twos <= 0
						|| (required_twos < 60 && IS_DIV_POW2(d.m, (uint32_t)required_twos));
					roundup = trailing_zeros ? ROUNDUP_IF_ODD : ROUNDUP_UNCONDITIONALLY;
				}
				if (maximum > 0)
					index = ft_append_c_digits(maximum, digits, result, index);
				break ;
			}

			++i;
		}
		if (roundup != ROUNDUP_NONE)
		{
			int round_index = index;
			int dot_index = 0;
			while (1)
			{
				--round_index;
				char c;
				if (round_index == -1 || (c = result[round_index], c == '-'))
				{
					result[round_index + 1] = '1';
					if (dot_index > 0)
					{
						result[dot_index] = '0';
						result[dot_index + 1] = '.';
					}
					result[index++] = '0';
					break ;
				}
				if (c == '.')
				{
					dot_index = round_index;
					continue ;
				}
				else if (c == '9')
				{
					result[round_index] = '0';
					roundup = ROUNDUP_UNCONDITIONALLY;
					continue ;
				}
				else
				{
					if (roundup == ROUNDUP_IF_ODD && c % 2 == 0)
						break ;
					result[round_index] = c + 1;
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
