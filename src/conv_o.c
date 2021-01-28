/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:49:23 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/28 15:50:55 by dpowdere         ###   ########.fr       */
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
	opts->min_digits = 1;
	opts->use_uppercase = CASE_DOES_NOT_MATTER;
	opts->sp = SIGN_PRESENTATION_MINUS_ONLY;
	if (spec->flags & FLAG_FIELD_WIDTH_ZERO_PAD && spec->width != UNSPECIFIED)
	{
		opts->min_digits = spec->width;
		if (opts->min_digits > 0 && eff == EFF_NUMBER_POSITIVE
				&& spec->flags & (FLAG_SHOW_PLUS | FLAG_SHOW_SPACE_PLUS))
			opts->min_digits -= 1;
	}
	else if (spec->precision != UNSPECIFIED)
		opts->min_digits = spec->precision;
	if (spec->flags & FLAG_SHOW_PLUS)
		opts->sp = SIGN_PRESENTATION_MINUS_PLUS;
	else if (spec->flags & FLAG_SHOW_SPACE_PLUS)
		opts->sp = SIGN_PRESENTATION_MINUS_SPACE;
}

void				ft_conv_o(t_toolbox *toolbox, va_list *arg_ptr)
{
	char					*s;
	size_t					typing_width;
	t_umax					n;
	t_effector				eff;
	t_int_format_options	opts;

	n = ft_get_unsigned_va_arg(arg_ptr, toolbox->spec.size);
	eff = (n == 0 ? EFF_NUMBER_ZERO : EFF_NUMBER_POSITIVE);
	ft_set_opts(&opts, &toolbox->spec, eff);
	s = ft_format_ju((t_umax)n, opts);
	if (toolbox->spec.flags & FLAG_ALTERNATIVE_FORM && s != NULL && s[0] != '0'
			&& !(toolbox->spec.precision == 0 && n == 0))
		s = ft_strpfx("0", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	if (toolbox->spec.flags & FLAG_SHOW_PLUS)
		s = ft_strpfx("+", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	else if (toolbox->spec.flags & FLAG_SHOW_SPACE_PLUS)
		s = ft_strpfx(" ", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	if (s == NULL)
	{
		toolbox->error = PRINTF_MALLOC_ERROR;
		return ;
	}
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}
