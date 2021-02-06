/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e_case1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:20:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 15:00:22 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

#define DO_BREAK	1
#define DONT_BREAK	0

static inline uint32_t	ft_mshm(t_decomposed_dbl *d, int32_t i,
								uint32_t ix, uint32_t p10bits)
{
	const uint64_t			m = d->m << 8;
	const uint64_t *const	mul = g_pow10_split[g_pow10_offset[ix] + i];
	const int32_t			j = (int32_t)((p10bits - d->e) + 8);

	return (ft_mul_shift_mod1e9(m, mul, j));
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
	d->exp = i * 9 + (int32_t)d->available_digits - 1;
	if (d->available_digits > (uint32_t)d->opts->precision)
		return (DO_BREAK);
	if (d->show_dot)
		*index = ft_append_d_digits(d->available_digits,
									d->digits, result, *index);
	else
		result[(*index)++] = (char)('0' + d->digits);
	d->printed_digits = d->available_digits;
	d->available_digits = 0;
	return (DONT_BREAK);
}

int						ft_format_e_case1(t_decomposed_dbl *d,
										char *const result, int index)
{
	uint32_t	ix;
	uint32_t	p10bits;
	int32_t		len;
	int32_t		i;

	ix = d->e < 0 ? 0 : IX4EXP((uint32_t)d->e);
	p10bits = POW10_BITS4IX(ix);
	len = (int32_t)LEN4IX(ix);
	i = len - 1;
	while (i >= 0)
	{
		d->digits = ft_mshm(d, i, ix, p10bits);
		if (d->printed_digits != 0)
		{
			if (ft_append_nine(d, result, &index) == DO_BREAK)
				break ;
		}
		else if (d->digits != 0)
			if (ft_append_d(d, i, result, &index) == DO_BREAK)
				break ;
		--i;
	}
	return (index);
}
