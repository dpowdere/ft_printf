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
#define DONT_FREE_PREFIX	0
#define DO_FREE_STRING		1

static inline void	ft_implementation(t_toolbox *toolbox, va_list *arg_ptr,
										int use_uppercase)
{
	unsigned int			n;
	char					*s;
	t_effector				eff;
	t_int_format_options	opts;
	size_t					typing_width;

	n = va_arg(*arg_ptr, unsigned int);
	eff = (n == 0 ? E_NUMBER_ZERO : E_NUMBER_NON_NEGATIVE);
	ft_normalize_spec(&toolbox->spec, eff);
	opts.base = 16;
	opts.use_uppercase = use_uppercase;
	opts.sp = SIGN_PRESENTATION_MINUS_ONLY;
	if (toolbox->spec.precision == UNDEFINED)
		opts.min_digits = 0;
	else
		opts.min_digits = toolbox->spec.precision;
	s = ft_format_llu((unsigned long long int)n, opts);
	if (toolbox->spec.show_plus)
		s = ft_strpfx("+", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	else if (toolbox->spec.show_space_plus)
		s = ft_strpfx(" ", s, DONT_FREE_PREFIX, DO_FREE_STRING);
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
