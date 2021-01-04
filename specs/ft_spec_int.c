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

void	ft_spec_i(t_toolbox *toolbox, va_list *arg_ptr)
{
	int						n;
	char					*s;
	t_int_format_options	opts;

	n = va_arg(*arg_ptr, int);
	opts.base = 10;
	opts.min_digits = toolbox->spec.precision;
	opts.use_uppercase = DOES_NOT_MATTER;
	opts.sp = SIGN_PRESENTATION_MINUS_ONLY;
	s = ft_format_lli((long long int)n, opts);
	ft_print_field(s, ft_strlen(s), toolbox);
	free(s);
}

void	ft_spec_u(t_toolbox *toolbox, va_list *arg_ptr)
{
	unsigned int			n;
	char					*s;
	t_int_format_options	opts;

	n = va_arg(*arg_ptr, unsigned int);
	opts.base = 10;
	opts.min_digits = toolbox->spec.precision;
	opts.use_uppercase = DOES_NOT_MATTER;
	opts.sp = SIGN_PRESENTATION_MINUS_ONLY;
	s = ft_format_llu((unsigned long long int)n, opts);
	ft_print_field(s, ft_strlen(s), toolbox);
	free(s);
}
