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
	if (DARWIN == 1)
		ft_print_field("%", 1, toolbox);
	else
	{
		ft_write(STDOUT, "%", 1);
		toolbox->cumulative_size += 1;
	}
}
