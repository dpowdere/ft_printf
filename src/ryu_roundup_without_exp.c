/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_roundup_without_exp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:17:11 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/28 20:19:40 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#define CONTINUE				0
#define STOP					1
#define STOP_AND_INCREMENT_IX	2

static inline int		ft_round(char *const result,
							int *round_index, int *dot_index,
							t_roundup *roundup)
{
	if (*round_index == -1 || result[*round_index] == '-')
	{
		result[*round_index + 1] = '1';
		if (*dot_index > 0)
		{
			result[*dot_index] = '0';
			result[*dot_index + 1] = '.';
		}
		return (STOP_AND_INCREMENT_IX);
	}
	if (result[*round_index] == '.')
		*dot_index = *round_index;
	else if (result[*round_index] == '9')
	{
		result[*round_index] = '0';
		*roundup = ROUNDUP_UNCONDITIONALLY;
	}
	else
	{
		if (*roundup == ROUNDUP_IF_ODD && result[*round_index] % 2 == 0)
			return (STOP);
		result[*round_index] = result[*round_index] + 1;
		return (STOP);
	}
	return (CONTINUE);
}

int						ft_roundup_without_exp(t_roundup roundup,
												char *const result,
												int index)
{
	int	round_index;
	int	dot_index;
	int	state;

	if (roundup != ROUNDUP_NEVER)
	{
		round_index = index - 1;
		dot_index = 0;
		while ((state = ft_round(result,
						&round_index, &dot_index, &roundup)) == CONTINUE)
			--round_index;
		if (state == STOP_AND_INCREMENT_IX)
			result[index++] = '0';
	}
	return (index);
}