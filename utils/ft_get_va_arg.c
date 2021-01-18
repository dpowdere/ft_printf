/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_va_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:36:33 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/11 18:37:29 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "libftprintf.h"

t_max	ft_get_signed_va_arg(va_list *ap, t_size type)
{
	if (type == SIZE_HH)
		return ((t_max)(signed char)va_arg(*ap, signed int));
	else if (type == SIZE_H)
		return ((t_max)(signed short int)va_arg(*ap, signed int));
	else if (type == SIZE_L)
		return ((t_max)(signed long int)va_arg(*ap, signed long int));
	else if (type == SIZE_LL)
		return ((t_max)(signed long long int)va_arg(*ap, signed long long int));
	else if (type == SIZE_T)
		return ((t_max)(ptrdiff_t)va_arg(*ap, ptrdiff_t));
	else if (type == SIZE_Z || type == SIZE_J)
		return ((t_max)(intmax_t)va_arg(*ap, intmax_t));
	return ((t_max)va_arg(*ap, signed int));
}

t_umax	ft_get_unsigned_va_arg(va_list *ap, t_size type)
{
	if (type == SIZE_HH)
		return ((t_max)(unsigned char)va_arg(*ap, unsigned int));
	else if (type == SIZE_H)
		return ((t_max)(unsigned short)va_arg(*ap, unsigned int));
	else if (type == SIZE_L)
		return ((t_max)(unsigned long)va_arg(*ap, unsigned long));
	else if (type == SIZE_LL)
		return ((t_max)(unsigned long long)va_arg(*ap, unsigned long long));
	else if (type == SIZE_Z)
		return ((t_max)(size_t)va_arg(*ap, size_t));
	else if (type == SIZE_T || type == SIZE_J)
		return ((t_max)(uintmax_t)va_arg(*ap, uintmax_t));
	return ((t_max)va_arg(*ap, unsigned int));
}
