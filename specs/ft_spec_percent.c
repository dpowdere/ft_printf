/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:35:09 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 18:35:11 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "../libftprintf.h"

void	ft_spec_percent(t_toolbox *toolbox, va_list *arg_ptr)
{
	(void)arg_ptr;
	ft_print_field("%", 1, toolbox);
}