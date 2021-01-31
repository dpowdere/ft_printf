/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_frac_without_exp.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:46:10 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/31 19:44:23 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

static inline uint32_t	ft_mshma(t_decomposed_dbl d,
								uint32_t p, int32_t tab_index)
{
	uint32_t digits;

	digits = ft_mul_shift_mod1e9(
		d.m << 8,
		g_pow10_split_2[p],
		ADDITIONAL_BITS_2 + (-d.e - 16 * tab_index) + 8);
	return (digits);
}

static inline int		ft_trailing_zeros(t_decomposed_dbl d)
{
	int32_t	required_twos;
	int		trailing_zeros;

	required_twos = -d.e - (int32_t)d.opts->precision - 1;
	trailing_zeros = required_twos <= 0 ||
		(required_twos < 60 && IS_DIV_POW2(d.m, (uint32_t)required_twos));
	return (trailing_zeros);
}

static inline uint32_t	ft_get_max_and_roundup_type(t_decomposed_dbl *d,
													uint32_t i,
													uint32_t *digits)
{
	uint32_t maximum;
	uint32_t last_digit;
	uint32_t j;

	maximum = d->opts->precision - 9 * i;
	last_digit = 0;
	j = 0;
	while (j++ < 9 - maximum)
	{
		last_digit = *digits % 10;
		*digits /= 10;
	}
	if (last_digit != 5)
		d->roundup = last_digit > 5 ? ROUNDUP_UNCONDITIONALLY : ROUNDUP_NEVER;
	else
		d->roundup = ft_trailing_zeros(*d) ? ROUNDUP_IF_ODD
										: ROUNDUP_UNCONDITIONALLY;
	return (maximum);
}

#define BREAK		0
#define CONTINUE	1

int						ft_fill_blocks(t_decomposed_dbl *d,
										int32_t tab_index, uint32_t i,
										struct s_result *r)
{
	uint32_t p;
	uint32_t digits;
	uint32_t maximum;

	p = g_pow10_offset_2[tab_index] + i - g_min_block_2[tab_index];
	if (p >= g_pow10_offset_2[tab_index + 1])
	{
		r->ix = ft_fill_zeros(d->opts->precision - 9 * i, r->result, r->ix);
		return (BREAK);
	}
	digits = ft_mshma(*d, p, tab_index);
	if (i < d->frac_blocks - 1)
		r->ix = ft_append_nine_digits(digits, r->result, r->ix);
	else
	{
		maximum = ft_get_max_and_roundup_type(d, i, &digits);
		if (maximum > 0)
			r->ix = ft_append_c_digits(maximum, digits, r->result, r->ix);
	}
	if (i >= d->frac_blocks - 1)
		return (BREAK);
	return (CONTINUE);
}

int						ft_format_f_frac(t_decomposed_dbl *d,
										char *const result, int index)
{
	int32_t			tab_index;
	uint32_t		i;
	struct s_result	r;

	tab_index = -d->e / 16;
	r.result = result;
	r.ix = index;
	i = 0;
	if (d->frac_blocks <= g_min_block_2[tab_index])
	{
		i = d->frac_blocks;
		r.ix = ft_fill_zeros(d->opts->precision, result, r.ix);
	}
	else if (i < g_min_block_2[tab_index])
	{
		i = g_min_block_2[tab_index];
		r.ix = ft_fill_zeros(9 * i, result, r.ix);
	}
	while (i < d->frac_blocks)
	{
		if (ft_fill_blocks(d, tab_index, i, &r) == BREAK)
			break ;
		++i;
	}
	return (r.ix);
}