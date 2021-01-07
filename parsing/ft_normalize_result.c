/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_result.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:55:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 19:55:45 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_normalize_directives(t_toolbox *toolbox)
{
	if (toolbox->spec.precision == UNDEFINED
			&& ft_strchr(NUM_SPECIRIERS, toolbox->spec.specifier))
		toolbox->spec.precision = 0;
}
