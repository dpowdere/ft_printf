/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:32:54 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/09 17:33:59 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "../libftprintf.h"

void	ft_spec_n(t_toolbox *toolbox, va_list *arg_ptr)
{
	*(va_arg(*arg_ptr, signed int *)) = (signed int)toolbox->cumulative_size;
}
