/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:29:24 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/23 11:29:27 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

int		ft_copy_special_str_printf(char *const result,
									const int sign,
									const uint64_t mantissa,
									const int use_uppercase)
{
	size_t	len;
	char	*s;

	if (mantissa)
	{
		s = use_uppercase ? FLT_NAN_UPPER : FLT_NAN_LOWER;
		len = ft_strlen(s);
		ft_memcpy(result, s, len);
		return (len);
	}
	if (sign)
		result[0] = '-';
	s = use_uppercase ? FLT_INF_UPPER : FLT_INF_LOWER;
	len = ft_strlen(s);
	ft_memcpy(result + sign, s, len);
	return (sign + len);
}
