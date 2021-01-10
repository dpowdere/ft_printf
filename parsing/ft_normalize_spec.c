/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_spec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:55:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 19:55:45 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "../libftprintf.h"

static inline void	ft_resolve_asterisks(t_spec *spec, va_list *arg_ptr)
{
	if (spec->width == TAKE_FROM_ARG)
	{
		spec->width = va_arg(*arg_ptr, int);
		if (spec->width < 0)
		{
			spec->width = -spec->width;
			spec->left_justify = YES;
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
	if (spec->show_space_plus && spec->show_plus)
		spec->show_space_plus = NO;
	match = ft_strchr(UNSIGNED_SPECIFIERS, spec->specifier);
	if (match && spec->show_space_plus)
		spec->show_space_plus = NO;
	if (match && spec->show_plus)
		spec->show_plus = NO;
	if (spec->left_justify)
		spec->zero_pad = NO;
	match = ft_strchr(INT_SPECIFIERS, spec->specifier);
	if (match && spec->precision != UNSPECIFIED)
		spec->zero_pad = NO;
	match = ft_strchr(NUM_SPECIFIERS, spec->specifier);
	if (match && spec->zero_pad)
		spec->field_width_zero_pad = YES;
}
