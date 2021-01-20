/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_mul_shift_mod1e9.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:11:09 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/20 12:11:13 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "ryu.h"

static inline void	ft_s1(const uint64_t m,
							const uint64_t *const mul,
							uint64_t *s1low,
							uint64_t *s1high)
{
	uint64_t hi0;
	uint64_t hi1;
	uint64_t hi2;
	uint64_t lo1;
	uint64_t lo2;

	(void)ft_umul128(m, mul[0], &hi0);
	lo1 = ft_umul128(m, mul[1], &hi1);
	lo2 = ft_umul128(m, mul[2], &hi2);
	*s1low = lo2 + hi1 + (lo1 + hi0 < lo1);
	*s1high = hi2 + (*s1low < lo2);
}

uint32_t			ft_mul_shift_mod1e9(const uint64_t m,
										const uint64_t *const mul,
										const int32_t j)
{
	uint64_t s1low;
	uint64_t s1high;

	ft_s1(m, mul, &s1low, &s1high);
	if (j < 160)
		return ((uint32_t)MOD1E9((uint64_t)((((uint64_t)(uint32_t)MOD1E9(
			(((uint64_t)(uint32_t)MOD1E9(s1high)) << 32) | (s1low >> 32)))
			<< 32) | (s1low & 0xffffffff)) >> (j - 128)));
	else
		return ((uint32_t)MOD1E9(((((uint64_t)(uint32_t)MOD1E9(s1high)) << 32)
			| (s1low >> 32)) >> (j - 160)));
}
/*
** (128 <= j <= 180)
*/
