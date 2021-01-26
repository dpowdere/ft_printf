/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_zero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:48:12 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/26 12:32:33 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

int		ft_is_zero(double n)
{
	const uint64_t bits = *(uint64_t *)&n;
	const uint64_t exp_segm = bits >> DBL_MANTISSA_BITS;
	const uint64_t exp_mask = ((uint64_t)1u << DBL_EXPONENT_BITS) - 1;
	const uint32_t exponent = (uint32_t)(exp_segm & exp_mask);
	const uint64_t mantissa = bits & (((uint64_t)1u << DBL_MANTISSA_BITS) - 1);

	return (exponent == 0 && mantissa == 0);
}

char	*ft_format_zero(t_float_format_options *opts, char *s, int ix)
{
	char *tmp;

	s[ix++] = '0';
	if (opts->precision > 0)
	{
		s[ix++] = '.';
		ft_memset(s + ix, '0', opts->precision);
		ix += opts->precision;
	}
	if (opts->output_type == FLOAT_EXPONENTIAL)
	{
		tmp = opts->use_uppercase ? FLT_EXP_ZERO_UPPER : FLT_EXP_ZERO_LOWER;
		ft_memcpy(s + ix, tmp, ft_strlen(tmp));
	}
	return (s);
}
