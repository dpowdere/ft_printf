/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:48:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:48:44 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

#define DO_USE_UPPERCASE	1
#define DONT_USE_UPPERCASE	0

static inline void	ft_implementation(t_toolbox *toolbox, va_list *arg_ptr,
										int use_uppercase)
{
	double		n;
	char		*s;
	char		*s2;
	size_t		typing_width;
	size_t		typing_width2;
	uint32_t	precision;

	n = va_arg(*arg_ptr, double);
	s = (char *)malloc(2000);
	s2 = (char *)malloc(2000);
	if (toolbox->spec.precision == UNSPECIFIED)
		precision = 6;
	else
		precision = toolbox->spec.precision;
	typing_width = ft_dtoa_f(n, s, precision, use_uppercase);
	s[typing_width] = '\0';
	typing_width2 = ft_dtoa_e(n, s2, precision, use_uppercase);
	s2[typing_width2] = '\0';
	if (typing_width > typing_width2)
	{
		free(s);
		typing_width = typing_width2;
		s = s2;
	}
	else
		free(s2);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}

void				ft_conv_g(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_implementation(toolbox, arg_ptr, DONT_USE_UPPERCASE);
}

void				ft_conv_upper_g(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_implementation(toolbox, arg_ptr, DO_USE_UPPERCASE);
}
