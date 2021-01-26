/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:32:45 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:00:41 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

/*
** Returns the number of decimal digits in v, which must not
** contain more than 9 digits.
**
** Function precondition: v is not a 10-digit number.
** (ft_dtoa_f: We print 9-digit blocks.)
** (v < 1000000000)
*/

uint32_t			ft_decimal_len9(const uint32_t v)
{
	if (v >= 100000000)
		return (9);
	if (v >= 10000000)
		return (8);
	if (v >= 1000000)
		return (7);
	if (v >= 100000)
		return (6);
	if (v >= 10000)
		return (5);
	if (v >= 1000)
		return (4);
	if (v >= 100)
		return (3);
	if (v >= 10)
		return (2);
	return (1);
}

/*
** Returns true if value is divisible by 5^p.
*/

int					ft_is_div_pow5(uint64_t value, uint32_t p)
{
	uint32_t count;
	uint32_t r;
	uint64_t q;

	count = 0;
	while (1)
	{
		q = value / 5;
		r = (uint32_t)value - 5 * (uint32_t)q;
		if (r != 0)
			break ;
		value = q;
		++count;
	}
	return (count >= p);
}

uint64_t			ft_umul128(const uint64_t a, const uint64_t b,
								uint64_t *const product_hi)
{
	const uint64_t b00 = (uint64_t)(uint32_t)a * (uint32_t)b;
	const uint64_t b01 = (uint64_t)(uint32_t)a * (uint32_t)(b >> 32);
	const uint64_t b10 = (uint64_t)(uint32_t)(a >> 32) * (uint32_t)b;
	const uint64_t mid1 = b10 + (uint32_t)(b00 >> 32);
	const uint64_t mid2 = b01 + (uint32_t)(mid1);

	*product_hi = ((uint64_t)(uint32_t)(a >> 32) * (uint32_t)(b >> 32))
		+ (uint32_t)(mid1 >> 32) + (uint32_t)(mid2 >> 32);
	return (((uint64_t)(uint32_t)mid2 << 32) | (uint32_t)b00);
}

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

/*
** (128 <= j <= 180)
*/

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
