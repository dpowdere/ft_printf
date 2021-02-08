/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:38:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/26 11:51:16 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

int	ft_is_float_negative(double n)
{
	const uint64_t	bits = *(uint64_t *)&n;
	const uint64_t	sign_bit = bits >> DBL_SIGN_BIT_SHIFT;
	const uint64_t	sign_mask = (uint64_t)1u;
	const int		sign = (int)(sign_bit & sign_mask);

	return (sign);
}

int	ft_format_sign(double n, t_float_format_options *opts, char *s)
{
	int	is_negative;
	int	cursor_shift;

	is_negative = ft_is_float_negative(n);
	cursor_shift = 1;
	if (is_negative)
		*s = '-';
	else if (!is_negative && opts->flags & FLAG_SHOW_PLUS)
		*s = '+';
	else if (!is_negative && opts->flags & FLAG_SHOW_SPACE_PLUS)
		*s = ' ';
	else
		cursor_shift = 0;
	return (cursor_shift);
}
