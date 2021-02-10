/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e_case3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:20:57 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 15:26:42 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

static inline uint32_t	ft_get_last_digit(t_decomposed_dbl *d, uint32_t maximum)
{
	uint32_t last_digit;
	uint32_t i;

	last_digit = 0;
	if (d->available_digits > maximum)
	{
		i = 0;
		while (i < d->available_digits - maximum)
		{
			last_digit = d->digits % 10;
			d->digits /= 10;
			++i;
		}
	}
	return (last_digit);
}

static inline void		ft_set_roundup(t_decomposed_dbl *d, uint32_t last_digit)
{
	int32_t	rexp;
	int32_t	required_twos;
	int		trailing_zeros;

	if (last_digit != 5)
		d->roundup = last_digit > 5 ? ROUNDUP_UNCONDITIONALLY : ROUNDUP_NEVER;
	else
	{
		rexp = (int32_t)d->opts->precision - d->exp;
		required_twos = -d->e - rexp;
		trailing_zeros = required_twos <= 0 ||
			(required_twos < 60 && IS_DIV_POW2(d->m, (uint32_t)required_twos));
		if (rexp < 0)
			trailing_zeros = trailing_zeros && ft_is_div_pow5(d->m, -rexp);
		d->roundup = trailing_zeros ? ROUNDUP_IF_ODD : ROUNDUP_UNCONDITIONALLY;
	}
}

int						ft_format_e_case3(t_decomposed_dbl *d,
										char *const result, int index)
{
	uint32_t maximum;

	maximum = d->opts->precision - d->printed_digits;
	if (d->available_digits == 0)
		d->digits = 0;
	ft_set_roundup(d, ft_get_last_digit(d, maximum));
	if (d->printed_digits != 0)
		index = ft_append_c_digits(maximum, d->digits, result, index);
	else
	{
		if (d->show_dot)
			index = ft_append_d_digits(maximum, d->digits, result, index);
		else
			result[index++] = (char)('0' + d->digits);
	}
	return (index);
}