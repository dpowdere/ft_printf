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

static inline void	ft_set_opts(t_int_format_options *opts, t_spec *spec,
								t_effector eff, int use_uppercase)
{
	opts->base = 16;
	opts->use_uppercase = use_uppercase;
	opts->min_digits = 1;
	opts->sp = SIGN_PRESENTATION_MINUS_ONLY;
	if (spec->field_width_zero_pad && spec->width != UNSPECIFIED)
	{
		opts->min_digits = spec->width;
		if (opts->min_digits > 0 && eff == E_NUMBER_POSITIVE
				&& (spec->show_plus || spec->show_space_plus))
			opts->min_digits -= 1;
		if (opts->min_digits > 1 && spec->alternative_form)
			opts->min_digits -= 2;
	}
	else if (spec->precision != UNSPECIFIED)
		opts->min_digits = spec->precision;
	if (spec->show_plus)
		opts->sp = SIGN_PRESENTATION_MINUS_PLUS;
	else if (spec->show_space_plus)
		opts->sp = SIGN_PRESENTATION_MINUS_SPACE;
}

static inline void	ft_implementation(t_toolbox *toolbox, va_list *arg_ptr,
										int use_uppercase)
{
	t_umax					n;
	char					*s;
	t_effector				eff;
	t_int_format_options	opts;
	size_t					typing_width;

	n = ft_get_unsigned_va_arg(arg_ptr, toolbox->spec.size);
	eff = (n == 0 ? E_NUMBER_ZERO : E_NUMBER_POSITIVE);
	if (eff == E_NUMBER_ZERO)
		toolbox->spec.alternative_form = NO;
	ft_set_opts(&opts, &toolbox->spec, eff, use_uppercase);
	s = ft_format_llu((t_umax)n, opts);
	if (toolbox->spec.alternative_form && !use_uppercase)
		s = ft_strpfx("0x", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	else if (toolbox->spec.alternative_form && use_uppercase)
		s = ft_strpfx("0X", s, DONT_FREE_PREFIX, DO_FREE_STRING);
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
