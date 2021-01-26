/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:48:37 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:48:38 by dpowdere         ###   ########.fr       */
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
	double					n;
	char					*s;
	size_t					typing_width;
	t_float_format_options	opts;

	n = va_arg(*arg_ptr, double);
	opts.output_type = FLOAT_FIXED;
	opts.precision = toolbox->spec.precision;
	opts.use_uppercase = use_uppercase;
	opts.sp = SIGN_PRESENTATION_MINUS_ONLY;
	if (toolbox->spec.precision == UNSPECIFIED)
		opts.precision = 6;
	if (toolbox->spec.flags & FLAG_SHOW_PLUS)
		opts.sp = SIGN_PRESENTATION_MINUS_PLUS;
	else if (toolbox->spec.flags & FLAG_SHOW_SPACE_PLUS)
		opts.sp = SIGN_PRESENTATION_MINUS_SPACE;
	s = ft_dtoa(n, &opts);
	if (s == NULL)
	{
		toolbox->error = PRINTF_MALLOC_ERROR;
		return ;
	}
	typing_width = ft_strlen(s);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}

void				ft_conv_f(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_implementation(toolbox, arg_ptr, DONT_USE_UPPERCASE);
}

void				ft_conv_upper_f(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_implementation(toolbox, arg_ptr, DO_USE_UPPERCASE);
}
