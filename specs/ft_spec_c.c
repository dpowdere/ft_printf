/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:32:32 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 18:32:35 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "../libftprintf.h"

void	ft_spec_c(t_toolbox *toolbox, va_list *arg_ptr)
{
	int c;

	c = va_arg(*arg_ptr, int);
	ft_print_field((char *)&c, 1, toolbox);
}