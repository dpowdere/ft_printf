/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:43:14 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:43:19 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_parse_flags(t_toolbox *toolbox)
{
	char	*c;

	while (*toolbox->cursor &&
			(c = ft_strchr(FLAG_SPECIFIERS, *toolbox->cursor)) != NULL)
	{
		if (*c == '0')
			toolbox->spec.flags |= FLAG_ZERO_PAD;
		else if (*c == '-')
			toolbox->spec.flags |= FLAG_LEFT_JUSTIFY;
		else if (*c == '+')
			toolbox->spec.flags |= FLAG_SHOW_PLUS;
		else if (*c == ' ')
			toolbox->spec.flags |= FLAG_SHOW_SPACE_PLUS;
		else if (*c == '#')
			toolbox->spec.flags |= FLAG_ALTERNATIVE_FORM;
		++toolbox->cursor;
	}
	if (*toolbox->cursor == '\0')
		toolbox->error = PRINTF_PARSE_ERROR;
}
