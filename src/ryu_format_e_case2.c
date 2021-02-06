/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e_case2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:20:51 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 15:15:57 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

#define DO_BREAK	1
#define DONT_BREAK	0

static inline uint32_t	ft_get_digits(t_decomposed_dbl *d,
									uint32_t p, int32_t ix)
{
	uint32_t digits;

	if (p >= g_pow10_offset_2[ix + 1])
		digits = 0;
	else
		digits = ft_mul_shift_mod1e9(
			d->m << 8,
			g_pow10_split_2[p],
			ADDITIONAL_BITS_2 + (-d->e - 16 * ix) + 8);
	return (digits);
}

static inline int		ft_append_nine(t_decomposed_dbl *d,
									char *const result, int *index)
{
	if (d->printed_digits + 9 > (uint32_t)d->opts->precision)
	{
		d->available_digits = 9;
		return (DO_BREAK);
	}
	*index = ft_append_nine_digits(d->digits, result, *index);
	d->printed_digits += 9;
	return (DONT_BREAK);
}

static inline int		ft_append_d(t_decomposed_dbl *d, int32_t i,
									char *const result, int *index)
{
	d->available_digits = ft_decimal_len9(d->digits);
	d->exp = -(i + 1) * 9 + (int32_t)d->available_digits - 1;
	if (d->available_digits > (uint32_t)d->opts->precision)
		return (DO_BREAK);
	if (d->show_dot)
		*index = ft_append_d_digits(d->available_digits, d->digits,
									result, *index);
	else
		result[(*index)++] = (char)('0' + d->digits);
	d->printed_digits = d->available_digits;
	d->available_digits = 0;
	return (DONT_BREAK);
}

int						ft_format_e_case2(t_decomposed_dbl *d,
										char *const result, int index)
{
	int32_t		ix;
	int32_t		i;
	uint32_t	p;

	ix = -d->e / 16;
	i = g_min_block_2[ix];
	while (i < 200)
	{
		p = g_pow10_offset_2[ix] + (uint32_t)i - g_min_block_2[ix];
		d->digits = ft_get_digits(d, p, ix);
		if (d->printed_digits != 0)
		{
			if (ft_append_nine(d, result, &index) == DO_BREAK)
				break ;
		}
		else if (d->digits != 0)
			if (ft_append_d(d, i, result, &index) == DO_BREAK)
				break ;
		++i;
	}
	return (index);
}
