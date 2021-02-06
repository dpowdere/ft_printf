/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_decompose_dbl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:17:14 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/31 19:47:39 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ryu.h"

static inline t_decomposed_dbl	ft_get_initialized_struct(
												t_float_format_options *opts)
{
	t_decomposed_dbl	d;

	d.e = 0;
	d.m = 0;
	d.opts = opts;
	d.roundup = ROUNDUP_NEVER;
	d.frac_blocks = opts->precision / 9 + 1;
	d.show_dot = opts->precision > 0 || opts->flags & FLAG_ALTERNATIVE_FORM;
	d.exp = 0;
	d.digits = 0;
	d.available_digits = 0;
	d.printed_digits = 0;
	return (d);
}

t_decomposed_dbl				ft_decompose_dbl(double n,
										t_float_format_options *opts)
{
	uint32_t			exponent;
	uint64_t			mantissa;
	uint64_t			segm;
	uint64_t			mask;
	t_decomposed_dbl	d;

	d = ft_get_initialized_struct(opts);
	segm = *(uint64_t *)&n >> DBL_MANTISSA_BITS;
	mask = ((uint64_t)1u << DBL_EXPONENT_BITS) - 1;
	exponent = (uint32_t)(segm & mask);
	segm = *(uint64_t *)&n;
	mask = ((uint64_t)1u << DBL_MANTISSA_BITS) - 1;
	mantissa = segm & mask;
	if (exponent == 0)
	{
		d.e = (int32_t)(1 - DBL_BIAS - DBL_MANTISSA_BITS);
		d.m = mantissa;
	}
	else
	{
		d.e = (int32_t)(exponent - DBL_BIAS - DBL_MANTISSA_BITS);
		d.m = ((uint64_t)1u << DBL_MANTISSA_BITS) | mantissa;
	}
	return (d);
}
