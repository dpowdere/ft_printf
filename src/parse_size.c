/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:43:44 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:43:46 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_parse_size(t_toolbox *toolbox)
{
	if (*toolbox->cursor == '\0')
		toolbox->error = PRINTF_PARSE_ERROR;
	if (*toolbox->cursor == 'h')
		toolbox->spec.size = SIZE_H;
	else if (*toolbox->cursor == 'l')
		toolbox->spec.size = SIZE_L;
	else if (*toolbox->cursor == 't')
		toolbox->spec.size = SIZE_T;
	else if (*toolbox->cursor == 'z')
		toolbox->spec.size = SIZE_Z;
	else if (*toolbox->cursor == 'j')
		toolbox->spec.size = SIZE_J;
	if (*(toolbox->cursor + 1))
	{
		if (*toolbox->cursor == 'h' && *(toolbox->cursor + 1) == 'h')
			toolbox->spec.size = SIZE_HH;
		else if (*toolbox->cursor == 'l' && *(toolbox->cursor + 1) == 'l')
			toolbox->spec.size = SIZE_LL;
	}
	if (toolbox->spec.size == SIZE_H || toolbox->spec.size == SIZE_L ||
			toolbox->spec.size == SIZE_T || toolbox->spec.size == SIZE_Z ||
			toolbox->spec.size == SIZE_J)
		toolbox->cursor += 1;
	else if (toolbox->spec.size == SIZE_HH || toolbox->spec.size == SIZE_LL)
		toolbox->cursor += 2;
}
