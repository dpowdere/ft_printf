/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_roundup_with_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 00:11:07 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/01 01:01:15 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#define CONTINUE				0
#define STOP					1

static inline int		ft_round(t_decomposed_dbl *d,
								char *const result, int round_index)
{
	if (round_index == -1 || result[round_index] == '-')
	{
		result[round_index + 1] = '1';
		++d->exp;
		return (STOP);
	}
	if (result[round_index] == '.')
		return (CONTINUE);
	else if (result[round_index] == '9')
	{
		result[round_index] = '0';
		d->roundup = ROUNDUP_UNCONDITIONALLY;
	}
	else
	{
		if (d->roundup == ROUNDUP_IF_ODD && result[round_index] % 2 == 0)
			return (STOP);
		result[round_index] += 1;
		return (STOP);
	}
	return (CONTINUE);
}

int						ft_roundup_e(t_decomposed_dbl *d,
									char *const result, int index)
{
	int round_index;

	if (d->roundup != ROUNDUP_NEVER)
	{
		round_index = index - 1;
		while (ft_round(d, result, round_index) == CONTINUE)
			--round_index;
	}
	return (index);
}
