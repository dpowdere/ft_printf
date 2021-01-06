/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:50:41 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 18:52:20 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_parse_flags(t_toolbox *toolbox)
{
	char	*c;

	while (*toolbox->cursor &&
			(c = ft_strchr(FLAG_SPECIFIERS, *toolbox->cursor)) != NULL)
	{
		if (*c == '0')
			toolbox->spec.zero_pad = 1;
		else if (*c == '-')
			toolbox->spec.left_justify = 1;
		++toolbox->cursor;
	}
	if (*toolbox->cursor == '\0')
		toolbox->error = PRINTF_NOSPEC_ERROR;
}
