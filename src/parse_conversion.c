/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:42:46 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:43:04 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libftprintf.h"

void	ft_parse_conversion(t_toolbox *toolbox)
{
	char *specifier;

	specifier = NULL;
	while (*toolbox->cursor &&
			(specifier = ft_strchr(CONV_SPECIFIERS, *toolbox->cursor)) == NULL)
		++toolbox->cursor;
	if (specifier == NULL)
	{
		toolbox->error = PRINTF_PARSE_ERROR;
		return ;
	}
	toolbox->spec.conversion = *specifier;
}
