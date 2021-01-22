/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:49:51 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:49:52 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "libftprintf.h"

void	ft_conv_c(t_toolbox *toolbox, va_list *arg_ptr)
{
	int c;

	c = va_arg(*arg_ptr, int);
	ft_print_field((char *)&c, 1, toolbox);
}
