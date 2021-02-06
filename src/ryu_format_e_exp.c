/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e_exp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:18:31 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 14:19:07 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_format_e_exp(t_decomposed_dbl *d, char *const result, int index)
{
	if (d->opts->flags & FLAG_USE_UPPERCASE)
		result[index++] = *FLT_EXP_UPPER;
	else
		result[index++] = *FLT_EXP_LOWER;
	if (d->exp < 0)
	{
		result[index++] = '-';
		d->exp = -d->exp;
	}
	else
		result[index++] = '+';
	if (d->exp >= 100)
	{
		ft_memcpy(result + index, g_digit_tab + 2 * (d->exp / 10), 2);
		result[index + 2] = (char)('0' + d->exp % 10);
		index += 3;
	}
	else
	{
		ft_memcpy(result + index, g_digit_tab + 2 * d->exp, 2);
		index += 2;
	}
	return (index);
}
