/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:34:29 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 18:34:32 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "../libftprintf.h"

#define DOES_NOT_MATTER 0

static inline void	ft_set_opts(t_int_format_options *opts, t_spec *spec,
								t_effector eff)
{
	opts->base = 10;
	opts->use_uppercase = DOES_NOT_MATTER;
	if (spec->field_width_zero_pad && spec->width != UNSPECIFIED)
	{
		opts->min_digits = spec->width;
		if (eff == E_NUMBER_NEGATIVE || (eff == E_NUMBER_POSITIVE &&
				(spec->show_plus || spec->show_space_plus)))
			if (opts->min_digits > 0)
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

void				ft_spec_i(t_toolbox *toolbox, va_list *arg_ptr)
{
	int						n;
	char					*s;
	t_effector				eff;
	t_int_format_options	opts;
	size_t					typing_width;

	n = va_arg(*arg_ptr, int);
	eff = E_NUMBER_ZERO;
	if (n > 0)
		eff = E_NUMBER_POSITIVE;
	if (n < 0)
		eff = E_NUMBER_NEGATIVE;
	ft_set_opts(&opts, &toolbox->spec, eff);
	s = ft_format_lli((long long int)n, opts);
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}

void				ft_spec_u(t_toolbox *toolbox, va_list *arg_ptr)
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
		eff = E_NUMBER_POSITIVE;
	ft_set_opts(&opts, &toolbox->spec, eff);
	s = ft_format_llu((unsigned long long int)n, opts);
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}
