/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_dtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:59:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/26 14:09:54 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libftprintf.h"

char	*ft_dtoa(double n, t_float_format_options *opts)
{
	int					ix;
	char				*s;
	t_decomposed_dbl	d;

	if ((s = ft_dtoa_malloc(opts)) == NULL)
		return (NULL);
	ix = ft_format_sign(n, opts, s);
	if (ft_is_nan_or_infinity(n))
		return (ft_format_nan_or_infinity(n, opts, s, ix));
	else if (ft_is_zero(n))
		return (ft_format_zero(opts, s, ix));
	d = ft_decompose_dbl(n);
	if (opts->output_type == FLOAT_EXPONENTIAL)
		return (ft_format_e(d, opts, s, ix));
	return (ft_format_f(d, opts, s, ix));
}
