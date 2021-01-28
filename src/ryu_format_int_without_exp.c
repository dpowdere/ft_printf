/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_int_without_exp.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:18:32 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/28 18:42:44 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

static inline uint32_t	ft_mshm(t_decomposed_dbl d,
								uint32_t tab_index, int32_t i)
{
	uint32_t	digits;

	digits = ft_mul_shift_mod1e9(
		d.m << 8,
		g_pow10_split[g_pow10_offset[tab_index] + i],
		(int32_t)((POW10_BITS4IX(tab_index) - d.e) + 8));
	return (digits);
}

int						ft_format_int_without_exp(t_decomposed_dbl d,
													char *const s, int ix)
{
	int			non_zero;
	int32_t		i;
	uint32_t	tab_index;
	uint32_t	digits;

	non_zero = 0;
	if (d.e >= -52)
	{
		tab_index = d.e < 0 ? 0 : IX4EXP((uint32_t)d.e);
		i = (int32_t)LEN4IX(tab_index);
		while (--i >= 0)
		{
			digits = ft_mshm(d, tab_index, i);
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
