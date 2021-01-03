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

#include "../libftprintf.h"

void	ft_spec_s(t_toolbox *toolbox, va_list *arg_ptr)
{
	char	*s;

	s = va_arg(*arg_ptr, char *);
	ft_print_field(s, ft_strlen(s), toolbox);
}
