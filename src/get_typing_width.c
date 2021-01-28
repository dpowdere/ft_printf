/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_typing_width.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:35:02 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/28 15:59:19 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libftprintf.h"

/*
** NOTE: When the string `s` is taken from arguments and is not a NULL pointer
** (EFF_STRING_NULL), but a valid pointer to char (EFF_STRING_NON_NULL), we must
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

	if (eff == EFF_STRING_NON_NULL && spec->precision >= 0)
	{
		typing_width = 0;
		while (typing_width < (size_t)spec->precision && s[typing_width])
			++typing_width;
	}
	else
	{
		typing_width = s == NULL ? 0 : ft_strlen(s);
		if ((eff == EFF_STRING_NULL && spec->precision >= 0
						&& (size_t)spec->precision < typing_width)
				|| (eff == EFF_NUMBER_ZERO && spec->precision == 0))
			typing_width = ON_MACOS ? spec->precision : 0;
		if (spec->flags & (FLAG_SHOW_PLUS | FLAG_SHOW_SPACE_PLUS) &&
				eff == EFF_NUMBER_ZERO && spec->precision == 0)
			typing_width = 1;
		if (spec->conversion == 'o' && eff == EFF_NUMBER_ZERO &&
				spec->precision == 0 && spec->flags & FLAG_ALTERNATIVE_FORM)
			typing_width = 1;
	}
	return (typing_width);
}
