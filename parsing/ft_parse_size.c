/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:51:34 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 18:52:26 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_parse_size(t_toolbox *toolbox)
{
	if (*toolbox->cursor == '\0')
		toolbox->error = PRINTF_PARSE_ERROR;
}
