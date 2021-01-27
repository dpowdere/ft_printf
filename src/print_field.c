/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:46:13 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/24 16:22:37 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

#define SPACE_CHAR	' '
#define ZERO_CHAR	'0'

static inline void	ft_printf_error(t_toolbox *toolbox, int error)
{
	toolbox->error = error;
}

static inline char	ft_get_pad_char(t_toolbox *toolbox)
{
	if (DARWIN == 1 && toolbox->spec.conversion == 's'
			&& toolbox->spec.flags & FLAG_ZERO_PAD)
		return (ZERO_CHAR);
	return (SPACE_CHAR);
}

void				ft_print_field(char *str, size_t str_size,
									t_toolbox *toolbox)
{
	char	*pad;
	int		pad_size;
	int		left_justify;

	left_justify = toolbox->spec.flags & FLAG_LEFT_JUSTIFY;
	pad_size = toolbox->spec.width - (int)str_size;
	if (pad_size > 0)
	{
		if ((pad = malloc(pad_size)) == NULL)
			return (ft_printf_error(toolbox, PRINTF_MALLOC_ERROR));
		ft_memset(pad, ft_get_pad_char(toolbox), pad_size);
		if (!left_justify && ft_write(STDOUT, pad, pad_size) < 0)
			ft_printf_error(toolbox, PRINTF_WRITE_ERROR);
	}
	if (ft_write(STDOUT, str, str_size) < 0)
		ft_printf_error(toolbox, PRINTF_WRITE_ERROR);
	if (pad_size > 0)
	{
		if (left_justify && ft_write(STDOUT, pad, pad_size) < 0)
			ft_printf_error(toolbox, PRINTF_WRITE_ERROR);
		free(pad);
	}
	toolbox->cumulative_size += (
			pad_size > 0 ? toolbox->spec.width : (int)str_size);
}
