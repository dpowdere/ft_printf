/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_spec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:55:43 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 19:55:45 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_normalize_spec(t_spec *spec, t_effector eff)
{
	if (spec->width >= 1 && spec->zero_pad && spec->precision == UNDEFINED &&
			!spec->left_justify && ft_strchr(NUM_SPECIRIERS, spec->specifier))
	{
		if (eff == E_NUMBER_NEGATIVE || (eff == E_NUMBER_NON_NEGATIVE &&
				(spec->show_plus || spec->show_space_plus)))
			spec->precision = spec->width - 1;
		else
			spec->precision = spec->width;
	}
	if (spec->precision == UNDEFINED
			&& ft_strchr(NUM_SPECIRIERS, spec->specifier))
		spec->precision = 0;
	if (spec->width == UNDEFINED)
		spec->width = 0;

}
