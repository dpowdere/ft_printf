/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:35:22 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/09 17:35:51 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

void	ft_spec_e(t_toolbox *toolbox, va_list *arg_ptr)
{
	double		n;
	char		*s;
	size_t		typing_width;
	uint32_t	preci;

	n = va_arg(*arg_ptr, double);
	s = (char *)malloc(2000);
	if (toolbox->spec.precision == UNSPECIFIED)
		preci = 6;
	else
		preci = toolbox->spec.precision;
	typing_width = d2exp_buffered_n(n, preci, s);
	s[typing_width] = '\0';
	ft_print_field(s, typing_width, toolbox);
	free(s);
}

void	ft_spec_upper_e(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_spec_e(toolbox, arg_ptr);
}
