/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:21 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/28 19:31:10 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char					*ft_format_f(t_decomposed_dbl d,
										t_float_format_options *opts,
										char *const result, int index)
{
	index = ft_format_int_without_exp(d, result, index);
	if (opts->precision > 0 || opts->flags & FLAG_ALTERNATIVE_FORM)
		result[index++] = '.';
	if (d.e < 0)
		index = ft_format_frac_without_exp(d, opts, result, index);
	else
		index = ft_fill_zeros(opts->precision, result, index);
	return (result);
}
