/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:35:24 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 18:35:30 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stddef.h>

#include "libftprintf.h"

void	ft_spec_s(t_toolbox *toolbox, va_list *arg_ptr)
{
	t_effector	eff;
	size_t		typing_width;
	char		*s;

	s = va_arg(*arg_ptr, char *);
	if (s == NULL)
	{
		s = NULL_STRING;
		eff = E_STRING_NULL;
	}
	else
		eff = E_STRING_NON_NULL;
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
}
