/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:57:49 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 18:09:16 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_parse_specifier(t_toolbox *toolbox)
{
	char *specifier;

	specifier = NULL;
	while (*toolbox->cursor &&
			(specifier = ft_strchr(SPECIFIERS, *toolbox->cursor)) == NULL)
		++toolbox->cursor;
	if (specifier == NULL)
	{
		toolbox->error = PRINTF_NOSPEC_ERROR;
		return ;
	}
	toolbox->spec.specifier = *specifier;
}
