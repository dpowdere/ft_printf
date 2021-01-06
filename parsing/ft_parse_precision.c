/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:51:48 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 18:52:29 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_parse_precision(t_toolbox *toolbox)
{
	int n;

	if (*toolbox->cursor && *toolbox->cursor == '.')
		++toolbox->cursor;
	n = 0;
	while (*toolbox->cursor &&
			*toolbox->cursor >= '0' && *toolbox->cursor <= '9')
	{
		n = n * 10 + (*toolbox->cursor - '0');
		++toolbox->cursor;
	}
	if (*toolbox->cursor == '\0')
	{
		toolbox->error = PRINTF_NOSPEC_ERROR;
		return ;
	}
	toolbox->spec.precision = n;
}
