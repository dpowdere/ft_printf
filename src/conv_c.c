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
#include <wchar.h>
#include <stdlib.h>

#include "libftprintf.h"

#define UTF8_MAX_BYTES_PER_CHAR		6
#define SINGLE_UTF8_CHAR_STRING		(UTF8_MAX_BYTES_PER_CHAR + 1)

/*
** See also stdlib's MB_CUR_MAX, wctomb, wcstombs.
*/

void	ft_conv_c(t_toolbox *toolbox, va_list *arg_ptr)
{
	int		c;
	int		len;
	char	s[SINGLE_UTF8_CHAR_STRING];

	if (toolbox->spec.size >= SIZE_L)
	{
		ft_memset(s, 0, SINGLE_UTF8_CHAR_STRING);
		if ((len = wctomb(s, va_arg(*arg_ptr, wchar_t))) == -1)
			toolbox->error = PRINTF_WCHAR_CONVERT_ERROR;
		ft_print_field((char *)s, len, toolbox);
	}
	else
	{
		c = va_arg(*arg_ptr, int);
		ft_print_field((char *)&c, 1, toolbox);
	}
}
