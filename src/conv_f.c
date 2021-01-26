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

void	ft_conv_f(t_toolbox *toolbox, va_list *arg_ptr)
{
	t_float_format_options	opts;
	size_t					typing_width;
	double					n;
	char					*s;

	n = va_arg(*arg_ptr, double);
	opts.output_type = FLOAT_FIXED;
	opts.precision = toolbox->spec.precision;
	opts.flags = toolbox->spec.flags;
	if (toolbox->spec.precision == UNSPECIFIED)
		opts.precision = 6;
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
