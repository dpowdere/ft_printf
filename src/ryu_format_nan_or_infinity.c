/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_nan_or_infinity.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:23:21 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/26 11:53:23 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

int		ft_is_nan_or_infinity(double n)
{
	const uint64_t bits = *(uint64_t *)&n;
	const uint64_t exp_mask = ((uint64_t)1u << DBL_EXPONENT_BITS) - 1;
	const uint64_t exp_segm = bits >> DBL_MANTISSA_BITS;
	const uint32_t exponent = (uint32_t)(exp_segm & exp_mask);

	return (exponent == (uint32_t)exp_mask);
}

char	*ft_format_nan_or_infinity(double n,
							t_float_format_options *opts,
							char *s, int ix)
{
	const uint64_t	bits = *(uint64_t *)&n;
	const uint64_t	mantissa_mask = ((uint64_t)1u << DBL_MANTISSA_BITS) - 1;
	const uint64_t	mantissa = bits & mantissa_mask;
	char			*tmp;

	if (mantissa)
	{
		tmp = opts->use_uppercase ? FLT_NAN_UPPER : FLT_NAN_LOWER;
		ft_memcpy(s + ix, tmp, ft_strlen(tmp));
		return (s);
	}
	tmp = opts->use_uppercase ? FLT_INF_UPPER : FLT_INF_LOWER;
	ft_memcpy(s + ix, tmp, ft_strlen(tmp));
	return (s);
}
