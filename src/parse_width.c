/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:43:56 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:43:57 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_parse_width(t_toolbox *toolbox)
{
	int			n;
	const char	*position;

	if (*toolbox->cursor && *toolbox->cursor == '*')
	{
		toolbox->spec.width = TAKE_FROM_ARG;
		++toolbox->cursor;
		return ;
	}
	n = 0;
	position = toolbox->cursor;
	while (*toolbox->cursor &&
			*toolbox->cursor >= '0' && *toolbox->cursor <= '9')
	{
		n = n * 10 + (*toolbox->cursor - '0');
		++toolbox->cursor;
	}
	if (position != toolbox->cursor)
		toolbox->spec.width = n;
	if (*toolbox->cursor == '\0')
		toolbox->error = PRINTF_PARSE_ERROR;
}
