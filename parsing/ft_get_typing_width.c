/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_typing_width.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:36:54 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/08 14:36:59 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "../libftprintf.h"

size_t	ft_get_typing_width(t_spec *spec, char *s, t_effector eff)
{
	size_t	typing_width;

	typing_width = s == NULL ? 0 : ft_strlen(s);
	if (spec->precision >= 0 && (size_t)spec->precision < typing_width)
	{
		if (eff == E_STRING_NULL)
			typing_width = 0;
		else if (eff == E_STRING_NON_NULL)
			typing_width = spec->precision;
	}
	if (spec->precision == 0 && eff == E_NUMBER_ZERO)
		typing_width = 0;
	return (typing_width);
}
