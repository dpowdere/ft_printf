/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:55:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 19:55:45 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "libftprintf.h"

static inline void	ft_resolve_asterisks(t_spec *spec, va_list *arg_ptr)
{
	if (spec->width == TAKE_FROM_ARG)
	{
		spec->width = va_arg(*arg_ptr, int);
		if (spec->width < 0)
		{
			spec->width = -spec->width;
			spec->flags |= FLAG_LEFT_JUSTIFY;
		}
		else if (spec->width == 0)
		{
			spec->width = UNSPECIFIED;
			spec->flags |= FLAG_ZERO_PAD;
		}
	}
	if (spec->precision == TAKE_FROM_ARG)
	{
		spec->precision = va_arg(*arg_ptr, int);
		if (spec->precision < 0)
			spec->precision = UNSPECIFIED;
	}
}

void				ft_normalize_spec(t_spec *spec, va_list *arg_ptr)
{
	char *match;

	ft_resolve_asterisks(spec, arg_ptr);
	if (spec->flags & FLAG_SHOW_SPACE_PLUS && spec->flags & FLAG_SHOW_PLUS)
		spec->flags &= ~FLAG_SHOW_SPACE_PLUS;
	match = ft_strchr(UNSIGNED_CONV_SPECIFIERS, spec->conversion);
	if (match && spec->flags & FLAG_SHOW_SPACE_PLUS)
		spec->flags &= ~FLAG_SHOW_SPACE_PLUS;
	if (match && spec->flags & FLAG_SHOW_PLUS)
		spec->flags &= ~FLAG_SHOW_PLUS;
	if (spec->flags & FLAG_LEFT_JUSTIFY)
		spec->flags &= ~FLAG_ZERO_PAD;
	match = ft_strchr(INT_CONV_SPECIFIERS, spec->conversion);
	if (match && spec->precision != UNSPECIFIED)
		spec->flags &= ~FLAG_ZERO_PAD;
	match = ft_strchr(NUM_CONV_SPECIFIERS, spec->conversion);
	if (match && spec->flags & FLAG_ZERO_PAD)
		spec->flags |= FLAG_FIELD_WIDTH_ZERO_PAD;
}
