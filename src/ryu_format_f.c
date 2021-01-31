/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:21 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/31 18:51:56 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char					*ft_format_f(t_decomposed_dbl d,
									char *const result, int index)
{
	index = ft_format_int_without_exp(d, result, index);
	if (d.show_dot)
		result[index++] = '.';
	if (d.e < 0)
	{
		index = ft_format_frac_without_exp(&d, result, index);
		index = ft_roundup_without_exp(&d, result, index);
	}
	else
		index = ft_fill_zeros(d.opts->precision, result, index);
	return (result);
}
