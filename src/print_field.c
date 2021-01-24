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

static inline void	ft_printf_error(t_toolbox *toolbox, int error)
{
	toolbox->error = error;
}

void				ft_print_field(char *str, size_t str_size,
									t_toolbox *toolbox)
{
	char	*pad;
	int		pad_size;

	pad_size = toolbox->spec.width - (int)str_size;
	if (pad_size > 0)
	{
		if ((pad = malloc(pad_size)) == NULL)
			return (ft_printf_error(toolbox, PRINTF_MALLOC_ERROR));
		ft_memset(pad, ' ', pad_size);
		if (!(toolbox->spec.flags & FLAG_LEFT_JUSTIFY)
				&& ft_write(STDOUT, pad, pad_size) < 0)
			ft_printf_error(toolbox, PRINTF_WRITE_ERROR);
	}
	if (ft_write(STDOUT, str, str_size) < 0)
		ft_printf_error(toolbox, PRINTF_WRITE_ERROR);
	if (pad_size > 0)
	{
		if (toolbox->spec.flags & FLAG_LEFT_JUSTIFY
				&& ft_write(STDOUT, pad, pad_size) < 0)
			ft_printf_error(toolbox, PRINTF_WRITE_ERROR);
		free(pad);
	}
	toolbox->cumulative_size += (
			pad_size > 0 ? toolbox->spec.width : (int)str_size);
}
