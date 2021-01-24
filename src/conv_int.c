/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:49:09 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:49:10 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

#define DOES_NOT_MATTER 0

static inline void	ft_set_opts(t_int_format_options *opts, t_spec *spec,
								t_effector eff)
{
	opts->base = 10;
	opts->use_uppercase = DOES_NOT_MATTER;
	opts->sp = SIGN_PRESENTATION_MINUS_ONLY;
	opts->min_digits = 1;
	if (spec->flags & FLAG_FIELD_WIDTH_ZERO_PAD && spec->width != UNSPECIFIED)
	{
		opts->min_digits = spec->width;
		if (eff == EFF_NUMBER_NEGATIVE || (eff == EFF_NUMBER_POSITIVE &&
				spec->flags & (FLAG_SHOW_PLUS | FLAG_SHOW_SPACE_PLUS)))
			if (opts->min_digits > 0)
				opts->min_digits -= 1;
	}
	else if (spec->precision != UNSPECIFIED)
		opts->min_digits = spec->precision;
	if (spec->flags & FLAG_SHOW_PLUS)
		opts->sp = SIGN_PRESENTATION_MINUS_PLUS;
	else if (spec->flags & FLAG_SHOW_SPACE_PLUS)
		opts->sp = SIGN_PRESENTATION_MINUS_SPACE;
}

void				ft_conv_i(t_toolbox *toolbox, va_list *arg_ptr)
{
	char					*s;
	size_t					typing_width;
	t_max					n;
	t_effector				eff;
	t_int_format_options	opts;

	n = ft_get_signed_va_arg(arg_ptr, toolbox->spec.size);
	eff = EFF_NUMBER_ZERO;
	if (n > 0)
		eff = EFF_NUMBER_POSITIVE;
	if (n < 0)
		eff = EFF_NUMBER_NEGATIVE;
	ft_set_opts(&opts, &toolbox->spec, eff);
	s = ft_format_ji(n, opts);
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}

void				ft_conv_d(t_toolbox *toolbox, va_list *arg_ptr)
{
	ft_conv_i(toolbox, arg_ptr);
}

void				ft_conv_u(t_toolbox *toolbox, va_list *arg_ptr)
{
	char					*s;
	size_t					typing_width;
	t_umax					n;
	t_effector				eff;
	t_int_format_options	opts;

	n = ft_get_unsigned_va_arg(arg_ptr, toolbox->spec.size);
	if (n == 0)
		eff = EFF_NUMBER_ZERO;
	else
		eff = EFF_NUMBER_POSITIVE;
	ft_set_opts(&opts, &toolbox->spec, eff);
	s = ft_format_ju(n, opts);
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}
