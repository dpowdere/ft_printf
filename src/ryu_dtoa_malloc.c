/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_dtoa_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:21:54 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/26 09:40:56 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

#define DBL_INTEGER_PART	309
#define DBL_INTEGER_SIGN	1
#define DBL_FRACTION_SIGN	1
#define DBL_EXPONENT_PART	5

#define C_STRING_TERMINATOR	1

char	*ft_dtoa_malloc(t_float_format_options *opts)
{
	char	*s;
	size_t	size;

	size = DBL_INTEGER_SIGN + DBL_INTEGER_PART + DBL_FRACTION_SIGN;
	if (opts->output_type == FLOAT_EXPONENTIAL)
		size += DBL_EXPONENT_PART;
	size += opts->precision;
	s = (char *)malloc((size + C_STRING_TERMINATOR) * sizeof(char));
	if (s != NULL)
		ft_memset(s, 0u, size + C_STRING_TERMINATOR);
	return (s);
}
