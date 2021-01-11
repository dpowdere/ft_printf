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

/*
** NOTE: When the string `s` is taken from arguments and is not a NULL pointer
** (E_STRING_NULL), but a valid pointer to char (E_STRING_NON_NULL), we must
** process its length in a special way:
**
**   - When precision is not specified, we should not care about `s`
**     being null-terminated. If we catch SEGFAULT, it is not our fault.
**
**   - When precision is specified and is not a negative number, we must
**     even gracefully process a non null-terminated string if it is
**     lengthy enough for the specified precision.
**
**   - If precision is greater than non null-terminated string, we may
**     catch SEGFAULT without any crisis of conscience.
*/

size_t	ft_get_typing_width(t_spec *spec, char *s, t_effector eff)
{
	size_t	typing_width;

	if (eff == E_STRING_NON_NULL && spec->precision >= 0)
	{
		typing_width = 0;
		while (typing_width < (size_t)spec->precision && s[typing_width])
			++typing_width;
	}
	else
	{
		typing_width = s == NULL ? 0 : ft_strlen(s);
		if ((eff == E_STRING_NULL && spec->precision >= 0
						&& (size_t)spec->precision < typing_width)
				|| (eff == E_NUMBER_ZERO && spec->precision == 0))
			typing_width = 0;
	}
	return (typing_width);
}
