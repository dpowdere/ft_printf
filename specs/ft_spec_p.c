/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:34:55 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/04 23:16:36 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>

#include "../libftprintf.h"

void	ft_spec_p(t_toolbox *toolbox, va_list *arg_ptr)
{
	void *p;
	char *s;

	p = va_arg(*arg_ptr, void *);
	s = ft_format_pointer(p, toolbox->spec.precision);
	ft_print_field(s, ft_strlen(s), toolbox);
	free(s);
}