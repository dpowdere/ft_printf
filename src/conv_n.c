/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:49:16 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:49:17 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "libftprintf.h"

void	ft_conv_n(t_toolbox *toolbox, va_list *ap)
{
	int		x;
	t_size	size;

	x = toolbox->cumulative_size;
	size = toolbox->spec.size;
	if (size == SIZE_HH)
		*(signed char *)(va_arg(*ap, signed int *)) = (signed char)x;
	else if (size == SIZE_H)
		*(signed short int *)(va_arg(*ap, signed int *)) = (signed short int)x;
	else if (size == SIZE_DEFAULT)
		*(va_arg(*ap, signed int *)) = (signed int)x;
	else if (size == SIZE_L)
		*(va_arg(*ap, signed long int *)) = (signed long int)x;
	else if (size == SIZE_LL)
		*(va_arg(*ap, signed long long int *)) = (signed long long int)x;
	else if (size == SIZE_T)
		*(va_arg(*ap, ptrdiff_t *)) = (ptrdiff_t)x;
	else if (size == SIZE_Z)
		*(va_arg(*ap, size_t *)) = (size_t)x;
	else if (size == SIZE_J)
		*(va_arg(*ap, intmax_t *)) = (intmax_t)x;
}
