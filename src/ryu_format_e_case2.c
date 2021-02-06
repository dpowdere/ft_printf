/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e_case2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:20:51 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 14:31:15 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

int		ft_format_e_case2(t_decomposed_dbl *d, char *const result, int index)
{
	int32_t		idx;
	int32_t		i;
	uint32_t	p;

	idx = -d->e / 16;
	i = g_min_block_2[idx];
	while (i < 200)
	{
		p = g_pow10_offset_2[idx] + (uint32_t)i - g_min_block_2[idx];
		d->digits = (p >= g_pow10_offset_2[idx + 1])
			? 0
			: ft_mul_shift_mod1e9(
				d->m << 8,
				g_pow10_split_2[p],
				ADDITIONAL_BITS_2 + (-d->e - 16 * idx) + 8);
		if (d->printed_digits != 0)
		{
			if (d->printed_digits + 9 > (uint32_t)d->opts->precision)
			{
				d->available_digits = 9;
				break ;
			}
			index = ft_append_nine_digits(d->digits, result, index);
			d->printed_digits += 9;
		}
		else if (d->digits != 0)
		{
			d->available_digits = ft_decimal_len9(d->digits);
			d->exp = -(i + 1) * 9 + (int32_t)d->available_digits - 1;
			if (d->available_digits > (uint32_t)d->opts->precision)
				break ;
			if (d->show_dot)
				index = ft_append_d_digits(d->available_digits, d->digits,
											result, index);
			else
				result[index++] = (char)('0' + d->digits);
			d->printed_digits = d->available_digits;
			d->available_digits = 0;
		}
		++i;
	}
	return (index);
}
