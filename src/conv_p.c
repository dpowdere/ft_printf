/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:49:30 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/28 14:59:26 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

#define DONT_USE_UPPERCASE	0
#define DONT_FREE_PREFIX	0
#define DO_FREE_STRING		1

static inline void	ft_set_opts(t_int_format_options *opts, t_spec *spec,
								t_effector eff)
{
	opts->base = 16;
	opts->min_digits = 1;
	opts->use_uppercase = DONT_USE_UPPERCASE;
	opts->sp = SIGN_PRESENTATION_MINUS_ONLY;
	if (spec->flags & FLAG_FIELD_WIDTH_ZERO_PAD && spec->width > 1)
	{
		opts->min_digits = spec->width - 2;
		if (opts->min_digits > 0 && eff == EFF_POINTER_NON_NULL
				&& spec->flags & (FLAG_SHOW_PLUS | FLAG_SHOW_SPACE_PLUS))
			opts->min_digits -= 1;
	}
	else if (spec->precision != UNSPECIFIED)
		opts->min_digits = spec->precision;
}

static inline void	ft_printf_error(t_toolbox *toolbox, int error)
{
	toolbox->error = error;
}

void				ft_conv_p(t_toolbox *toolbox, va_list *arg_ptr)
{
	void					*p;
	char					*s;
	t_effector				eff;
	t_int_format_options	opts;

	p = va_arg(*arg_ptr, void *);
	eff = (p == NULL ? EFF_POINTER_NULL : EFF_POINTER_NON_NULL);
	if (p == NULL && !ON_MACOS)
		s = ft_strdup(PTR_NULL);
	else if (p == NULL && ON_MACOS && toolbox->spec.precision == 0)
		s = ft_strdup("0x");
	else
	{
		ft_set_opts(&opts, &toolbox->spec, eff);
		s = ft_format_ju((t_umax)p, opts);
		s = ft_strpfx("0x", s, DONT_FREE_PREFIX, DO_FREE_STRING);
		if (toolbox->spec.flags & FLAG_SHOW_PLUS)
			s = ft_strpfx("+", s, DONT_FREE_PREFIX, DO_FREE_STRING);
		else if (toolbox->spec.flags & FLAG_SHOW_SPACE_PLUS)
			s = ft_strpfx(" ", s, DONT_FREE_PREFIX, DO_FREE_STRING);
		if (s == NULL)
			return (ft_printf_error(toolbox, PRINTF_MALLOC_ERROR));
	}
	ft_print_field(s, ft_get_typing_width(&toolbox->spec, s, eff), toolbox);
	free(s);
}
