/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:26:30 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/09 17:32:27 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>

#include "../libftprintf.h"

#define CASE_DOES_NOT_MATTER	0

void	ft_spec_o(t_toolbox *toolbox, va_list *arg_ptr)
{
	unsigned int			n;
	char					*s;
	t_int_format_options	opts;

	n = va_arg(*arg_ptr, unsigned int);
	opts.base = 8;
	opts.use_uppercase = CASE_DOES_NOT_MATTER;
	opts.sp = SIGN_PRESENTATION_MINUS_ONLY;
	if (toolbox->spec.precision == UNSPECIFIED)
		opts.min_digits = 1;
	else
		opts.min_digits = toolbox->spec.precision;
	s = ft_format_llu((unsigned long long int)n, opts);
	ft_print_field(s, ft_strlen(s), toolbox);
	free(s);
}
