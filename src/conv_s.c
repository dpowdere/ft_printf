/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:49:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:49:44 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>

#include "libftprintf.h"

static inline void	ft_conv_s_char(t_toolbox *toolbox, va_list *arg_ptr)
{
	t_effector	eff;
	size_t		typing_width;
	char		*s;

	s = va_arg(*arg_ptr, char *);
	if (s == NULL)
	{
		s = STR_NULL;
		eff = EFF_STRING_NULL;
	}
	else
		eff = EFF_STRING_NON_NULL;
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
}

static inline char	*ft___wcstombs_malloc(t_toolbox *toolbox, wchar_t *ws)
{
	size_t	len;
	char	*s;

	len = ft_wcstombs_len(ws);
	s = (char *)malloc(len + 1);
	if (s == NULL)
	{
		toolbox->error = PRINTF_MALLOC_ERROR;
		return (NULL);
	}
	ft_memset(s, 0, len + 1);
	if (ft_wcstombs(s, ws, len + 1) == (size_t)-1)
	{
		toolbox->error = PRINTF_WCHAR_CONVERT_ERROR;
		return (NULL);
	}
	return (s);
}

static inline void	ft_conv_s_wchar(t_toolbox *toolbox, va_list *arg_ptr)
{
	t_effector	eff;
	size_t		typing_width;
	wchar_t		*ws;
	char		*s;

	ws = va_arg(*arg_ptr, wchar_t *);
	if (ws == NULL)
	{
		s = STR_NULL;
		eff = EFF_STRING_NULL;
	}
	else
	{
		s = ft___wcstombs_malloc(toolbox, ws);
		if (s == NULL)
			return ;
		eff = EFF_STRING_NON_NULL;
	}
	typing_width = ft_get_typing_width(&toolbox->spec, s, eff);
	ft_print_field(s, typing_width, toolbox);
	if (ws == NULL)
		free(s);
}

void				ft_conv_s(t_toolbox *toolbox, va_list *arg_ptr)
{
	if ((toolbox->spec.size == SIZE_L && DARWIN) ||
			(toolbox->spec.size >= SIZE_L && !DARWIN))
		ft_conv_s_wchar(toolbox, arg_ptr);
	else
		ft_conv_s_char(toolbox, arg_ptr);
}
