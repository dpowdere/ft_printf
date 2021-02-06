/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_dtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:59:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 18:30:26 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

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
	d = ft_decompose_dbl(n, opts);
	if (opts->output_type == FLOAT_EXPONENTIAL)
		return (ft_format_e(d, s, ix));
	return (ft_format_f(d, s, ix));
}

int		ft_dtoa_get_exp(double n, t_float_format_options *opts)
{
	int					ix;
	char				*s;
	t_decomposed_dbl	d;

	if ((s = ft_dtoa_malloc(opts)) == NULL)
		return (DBL_EXP_MALLOC_ERROR);
	ix = ft_format_sign(n, opts, s);
	d = ft_decompose_dbl(n, opts);
	++d.opts->precision;
	if (d.e >= -52)
		ix = ft_format_e_case1(&d, s, ix);
	if (d.e < 0 && d.available_digits == 0)
		ix = ft_format_e_case2(&d, s, ix);
	ix = ft_format_e_case3(&d, s, ix);
	ix = ft_roundup_e(&d, s, ix);
	ix = ft_format_e_exp(&d, s, ix);
	free(s);
	return (d.exp);
}
