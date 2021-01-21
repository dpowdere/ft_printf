/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:36:00 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/09 17:36:17 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

void	ft_spec_f(t_toolbox *toolbox, va_list *arg_ptr)
{
	double		n;
	char		*s;
	size_t		typing_width;
	uint32_t	precision;

	n = va_arg(*arg_ptr, double);
	s = (char *)malloc(2000);
	if (toolbox->spec.precision == UNSPECIFIED)
		precision = 6;
	else
		precision = toolbox->spec.precision;
	typing_width = ft_dtoa_f(n, precision, s);
	s[typing_width] = '\0';
	ft_print_field(s, typing_width, toolbox);
	free(s);
}

void	ft_spec_upper_f(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_spec_f(toolbox, arg_ptr);
}
