/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:33:20 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 18:33:22 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "../libftprintf.h"

#define USE_UPPERCASE		1
#define DONT_USE_UPPERCASE	0

static inline void	ft_implementation(t_toolbox *toolbox, va_list *arg_ptr,
										int use_uppercase)
{
	unsigned int			n;
	char					*s;
	t_effector				eff;
	t_int_format_options	opts;
	size_t					typing_width;

	n = va_arg(*arg_ptr, unsigned int);
	if (n == 0)
		eff = E_NUMBER_ZERO;
	else
		eff = E_NUMBER_NON_NEGATIVE;
	ft_normalize_spec(&toolbox->spec, eff);
	opts.base = 16;
	opts.min_digits = toolbox->spec.precision;
	opts.use_uppercase = use_uppercase;
	opts.sp = SIGN_PRESENTATION_MINUS_ONLY;
	s = ft_format_llu((unsigned long long int)n, opts);
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}

void				ft_spec_x(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_implementation(toolbox, arg_ptr, DONT_USE_UPPERCASE);
}

void				ft_spec_upper_x(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_implementation(toolbox, arg_ptr, USE_UPPERCASE);
}
