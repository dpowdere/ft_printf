/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_digits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:24:04 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 19:24:07 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

/*
** Convert `digits` to a sequence of decimal digits. Append the digits to the
** `s` result. The caller has to guarantee that:
**
**   10^(x-1) <= digits < 10^x
**
** e.g., by passing `x` as `ft_decimal_len9(digits)`.
*/

int					ft_append_n_digits(const uint32_t x, uint32_t digits,
										char *const s, int ix)
{
	uint32_t i;
	uint32_t c;

	i = 0;
	while (digits >= 10000)
	{
		c = MOD(digits, 10000);
		digits /= 10000;
		ft_memcpy(s + ix + x - i - 2, g_digit_tab + ((c % 100) << 1), 2);
		ft_memcpy(s + ix + x - i - 4, g_digit_tab + ((c / 100) << 1), 2);
		i += 4;
	}
	if (digits >= 100)
	{
		c = (digits % 100) << 1;
		digits /= 100;
		ft_memcpy(s + ix + x - i - 2, g_digit_tab + c, 2);
		i += 2;
	}
	if (digits >= 10)
		ft_memcpy(s + ix + x - i - 2, g_digit_tab + (digits << 1), 2);
	else
		s[ix] = (char)('0' + digits);
	return (ix + x);
}

static inline void	ft_append_dot(uint32_t digits, char *const s, int ix)
{
	uint32_t c;

	if (digits >= 10)
	{
		c = digits << 1;
		s[ix + 2] = g_digit_tab[c + 1];
		s[ix + 1] = '.';
		s[ix] = g_digit_tab[c];
	}
	else
	{
		s[ix + 1] = '.';
		s[ix] = (char)('0' + digits);
	}
}

/*
** Convert `digits` to a sequence of decimal digits. Print the first digit,
** followed by a decimal dot '.' followed by the remaining digits. The caller
** has to guarantee that:
**
**   10^(x-1) <= digits < 10^x
**
** e.g., by passing `x` as `ft_decimal_len9(digits)`.
*/

int					ft_append_d_digits(const uint32_t x, uint32_t digits,
										char *const s, int ix)
{
	uint32_t i;
	uint32_t c;

	i = 0;
	while (digits >= 10000)
	{
		c = MOD(digits, 10000);
		digits /= 10000;
		ft_memcpy(s + ix + x + 1 - i - 2, g_digit_tab + ((c % 100) << 1), 2);
		ft_memcpy(s + ix + x + 1 - i - 4, g_digit_tab + ((c / 100) << 1), 2);
		i += 4;
	}
	if (digits >= 100)
	{
		c = ((digits % 100) << 1);
		digits /= 100;
		ft_memcpy(s + ix + x + 1 - i - 2, g_digit_tab + c, 2);
		i += 2;
	}
	ft_append_dot(digits, s, ix);
	return (ix + x + 1);
}

/*
** Convert `digits` to decimal and write the last `x` decimal digits to `s`
** result. If `digits` contains additional digits, then those are silently
** ignored. (Copy pairs of digits from g_digit_tab. Generate the last digit
** if x is odd.)
*/

int					ft_append_c_digits(const uint32_t x, uint32_t digits,
										char *const s, int ix)
{
	uint32_t i;
	uint32_t c;

	if (digits == 0)
		ft_memset(s + ix, '0', x);
	else
	{
		i = 0;
		while (i < x - 1)
		{
			c = ((digits % 100) << 1);
			digits /= 100;
			ft_memcpy(s + ix + x - i - 2, g_digit_tab + c, 2);
			i += 2;
		}
		if (i < x)
			s[ix + x - i - 1] = (char)('0' + (digits % 10));
	}
	return (ix + x);
}

/*
** Convert `digits` to decimal and write the last 9 decimal digits to
** `s` result. If `digits` contains additional digits, then those are
** silently ignored.
*/

int					ft_append_nine_digits(uint32_t digits,
											char *const s, int ix)
{
	uint32_t i;
	uint32_t c;

	if (digits == 0)
		ft_memset(s + ix, '0', 9);
	else
	{
		i = 0;
		while (i < 5)
		{
			c = MOD(digits, 10000);
			digits /= 10000;
			ft_memcpy(s + ix + 7 - i, g_digit_tab + ((c % 100) << 1), 2);
			ft_memcpy(s + ix + 5 - i, g_digit_tab + ((c / 100) << 1), 2);
			i += 4;
		}
		s[ix] = (char)('0' + digits);
	}
	return (ix + 9);
}
