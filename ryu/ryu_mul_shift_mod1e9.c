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

uint32_t	ft_mul_shift_mod1e9(const uint64_t m,
								const uint64_t *const mul,
								const int32_t j)
{
	uint64_t high0;																	 // 64
	const uint64_t low0 = ft_umul128(m, mul[0], &high0); // 0
	uint64_t high1;																	 // 128
	const uint64_t low1 = ft_umul128(m, mul[1], &high1); // 64
	uint64_t high2;																	 // 192
	const uint64_t low2 = ft_umul128(m, mul[2], &high2); // 128
	const uint64_t s0low = low0;							// 0
	(void) s0low; // unused
	const uint64_t s0high = low1 + high0;		 // 64
	const uint32_t c1 = s0high < low1;
	const uint64_t s1low = low2 + high1 + c1; // 128
	const uint32_t c2 = s1low < low2; // high1 + c1 can't overflow, so compare against low2
	const uint64_t s1high = high2 + c2;			 // 192
	// (128 <= j <= 180)
	if (j < 160)
	{ // j: [128, 160)
		const uint64_t r0 = (uint32_t)MOD1E9(s1high);
		const uint64_t r1 = (uint32_t)MOD1E9((r0 << 32) | (s1low >> 32));
		const uint64_t r2 = ((r1 << 32) | (s1low & 0xffffffff));
		return ((uint32_t)MOD1E9(r2 >> (j - 128)));
	}
	else
	{ // j: [160, 192)
		const uint64_t r0 = (uint32_t)MOD1E9(s1high);
		const uint64_t r1 = ((r0 << 32) | (s1low >> 32));
		return ((uint32_t)MOD1E9(r1 >> (j - 160)));
	}
}
