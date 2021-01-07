/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:35:24 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 18:35:30 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stddef.h>

#include "../libftprintf.h"

void	ft_spec_s(t_toolbox *toolbox, va_list *arg_ptr)
{
	char	*s;
	int		is_arg_null;
	size_t	max_len;

	s = va_arg(*arg_ptr, char *);
	is_arg_null = s == NULL;
	if (is_arg_null)
		s = NULL_STRING;
	max_len = ft_strlen(s);
	if (toolbox->spec.precision >= 0
			&& (size_t)toolbox->spec.precision < max_len)
		max_len = (is_arg_null ? 0 : toolbox->spec.precision);
	ft_print_field(s, max_len, toolbox);
}
