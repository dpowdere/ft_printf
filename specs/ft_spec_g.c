/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_g.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:36:26 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/09 17:36:49 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "../libftprintf.h"
#include "../include/ryu.h"

void	ft_spec_g(t_toolbox *toolbox, va_list *arg_ptr)
{
	double		n;
	char		*s;
	char		*s2;
	size_t		typing_width;
	size_t		typing_width2;
	uint32_t	preci;

	n = va_arg(*arg_ptr, double);
	s = (char *)malloc(2000);
	s2 = (char *)malloc(2000);
	if (toolbox->spec.precision == UNSPECIFIED)
		preci = 6;
	else
		preci = toolbox->spec.precision;
	typing_width = d2fixed_buffered_n(n, preci, s);
	s[typing_width] = '\0';
	typing_width2 = d2exp_buffered_n(n, preci, s2);
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

void	ft_spec_upper_g(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_spec_g(toolbox, arg_ptr);
}
