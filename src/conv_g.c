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

void				ft_conv_g(t_toolbox *toolbox, va_list *arg_ptr)
{
	t_float_format_options	opts;
	size_t					typing_width;
	size_t					typing_width2;
	char					*s;
	char					*s2;
	double					n;

	n = va_arg(*arg_ptr, double);
	opts.output_type = FLOAT_FIXED;
	opts.precision = toolbox->spec.precision;
	opts.flags = toolbox->spec.flags;
	if (toolbox->spec.precision == UNSPECIFIED)
		opts.precision = 6;
	else if (toolbox->spec.precision == 0)
		opts.precision = 1;
	s = ft_dtoa(n, &opts);
	if (s == NULL)
	{
		toolbox->error = PRINTF_MALLOC_ERROR;
		return ;
	}
	opts.output_type = FLOAT_EXPONENTIAL;
	s2 = ft_dtoa(n, &opts);
	if (s == NULL)
	{
		toolbox->error = PRINTF_MALLOC_ERROR;
		return ;
	}
	typing_width = ft_strlen(s);
	typing_width2 = ft_strlen(s2);
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
