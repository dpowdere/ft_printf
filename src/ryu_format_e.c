/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:44 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 14:24:42 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_format_e(t_decomposed_dbl d, char *const result, int index)
{
	++d.opts->precision;
	if (d.e >= -52)
		index = ft_format_e_case1(&d, result, index);
	if (d.e < 0 && d.available_digits == 0)
		index = ft_format_e_case2(&d, result, index);
	index = ft_format_e_case3(&d, result, index);
	index = ft_roundup_e(&d, result, index);
	index = ft_format_e_exp(&d, result, index);
	return (result);
}
