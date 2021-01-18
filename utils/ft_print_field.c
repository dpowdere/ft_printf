/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 17:25:58 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 18:01:10 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

void	ft_print_field(char *str, size_t str_size, t_toolbox *toolbox)
{
	char	*pad;
	int		pad_size;

	pad_size = toolbox->spec.width - (int)str_size;
	if (pad_size > 0)
	{
		if ((pad = malloc(pad_size)) == NULL)
		{
			toolbox->error = PRINTF_MALLOC_ERROR;
			return ;
		}
		ft_memset(pad, ' ', pad_size);
		if (!toolbox->spec.left_justify && ft_write(STDOUT, pad, pad_size) < 0)
			toolbox->error = PRINTF_WRITE_ERROR;
	}
	if (ft_write(STDOUT, str, str_size) < 0)
		toolbox->error = PRINTF_WRITE_ERROR;
	if (pad_size > 0)
	{
		if (toolbox->spec.left_justify && ft_write(STDOUT, pad, pad_size) < 0)
			toolbox->error = PRINTF_WRITE_ERROR;
		free(pad);
	}
	toolbox->cumulative_size += (
			pad_size > 0 ? toolbox->spec.width : (int)str_size);
}
