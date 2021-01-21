/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:49:23 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:49:24 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

#define CASE_DOES_NOT_MATTER	0
#define DONT_FREE_PREFIX		0
#define DO_FREE_STRING			1

static inline void	ft_set_opts(t_int_format_options *opts, t_spec *spec,
								t_effector eff)
{
	opts->base = 8;
	opts->use_uppercase = CASE_DOES_NOT_MATTER;
	if (spec->field_width_zero_pad && spec->width != UNSPECIFIED)
	{
		opts->min_digits = spec->width;
		if (opts->min_digits > 0 && eff == E_NUMBER_POSITIVE
				&& (spec->show_plus || spec->show_space_plus))
			opts->min_digits -= 1;
	}
	else if (spec->precision != UNSPECIFIED)
		opts->min_digits = spec->precision;
	else
		opts->min_digits = 1;
	if (spec->show_plus)
		opts->sp = SIGN_PRESENTATION_MINUS_PLUS;
	else if (spec->show_space_plus)
		opts->sp = SIGN_PRESENTATION_MINUS_SPACE;
	else
		opts->sp = SIGN_PRESENTATION_MINUS_ONLY;
}

void				ft_conv_o(t_toolbox *toolbox, va_list *arg_ptr)
{
	char					*s;
	size_t					typing_width;
	t_umax					n;
	t_effector				eff;
	t_int_format_options	opts;

	n = ft_get_unsigned_va_arg(arg_ptr, toolbox->spec.size);
	eff = (n == 0 ? E_NUMBER_ZERO : E_NUMBER_POSITIVE);
	ft_set_opts(&opts, &toolbox->spec, eff);
	s = ft_format_ju((t_umax)n, opts);
	if (toolbox->spec.alternative_form && s[0] != '0'
			&& !(toolbox->spec.precision == 0 && n == 0))
		s = ft_strpfx("0", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	if (toolbox->spec.show_plus)
		s = ft_strpfx("+", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	else if (toolbox->spec.show_space_plus)
		s = ft_strpfx(" ", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}
