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
** result. The caller has to guarantee that:
**
**   10^(olen-1) <= digits < 10^olen
**
** e.g., by passing `olen` as `ft_decimal_len9(digits)`.
*/

void	ft_append_n_digits(const uint32_t olen,
							uint32_t digits,
							char *const result)
{
	uint32_t i;
	uint32_t c;

	i = 0;
	while (digits >= 10000)
	{
		c = MOD(digits, 10000);
		digits /= 10000;
		ft_memcpy(result + olen - i - 2, g_digit_tab + ((c % 100) << 1), 2);
		ft_memcpy(result + olen - i - 4, g_digit_tab + ((c / 100) << 1), 2);
		i += 4;
	}
	if (digits >= 100)
	{
		c = (digits % 100) << 1;
		digits /= 100;
		ft_memcpy(result + olen - i - 2, g_digit_tab + c, 2);
		i += 2;
	}
	if (digits >= 10)
		ft_memcpy(result + olen - i - 2, g_digit_tab + (digits << 1), 2);
	else
		result[0] = (char)('0' + digits);
}

void	ft_append_dot(uint32_t digits, char *const result)
{
	uint32_t c;

	if (digits >= 10)
	{
		c = digits << 1;
		result[2] = g_digit_tab[c + 1];
		result[1] = '.';
		result[0] = g_digit_tab[c];
	}
	else
	{
		result[1] = '.';
		result[0] = (char)('0' + digits);
	}
}

/*
** Convert `digits` to a sequence of decimal digits. Print the first digit,
** followed by a decimal dot '.' followed by the remaining digits. The caller
** has to guarantee that:
**
**   10^(olen-1) <= digits < 10^olen
**
** e.g., by passing `olen` as `ft_decimal_len9(digits)`.
*/

void	ft_append_d_digits(const uint32_t olen,
							uint32_t digits,
							char *const result)
{
	uint32_t i;
	uint32_t c;

	i = 0;
	while (digits >= 10000)
	{
		c = MOD(digits, 10000);
		digits /= 10000;
		ft_memcpy(result + olen + 1 - i - 2, g_digit_tab + ((c % 100) << 1), 2);
		ft_memcpy(result + olen + 1 - i - 4, g_digit_tab + ((c / 100) << 1), 2);
		i += 4;
	}
	if (digits >= 100)
	{
		c = ((digits % 100) << 1);
		digits /= 100;
		ft_memcpy(result + olen + 1 - i - 2, g_digit_tab + c, 2);
		i += 2;
	}
	ft_append_dot(digits, result);
}

/*
** Convert `digits` to decimal and write the last `count` decimal digits to
** result. If `digits` contains additional digits, then those are silently
** ignored. (Copy pairs of digits from g_digit_tab. Generate the last digit
** if count is odd.)
*/

void	ft_append_c_digits(const uint32_t count,
							uint32_t digits,
							char *const result)
{
	uint32_t i;
	uint32_t c;

	i = 0;
	while (i < count - 1)
	{
		c = ((digits % 100) << 1);
		digits /= 100;
		ft_memcpy(result + count - i - 2, g_digit_tab + c, 2);
		i += 2;
	}
	if (i < count)
		result[count - i - 1] = (char)('0' + (digits % 10));
}

/*
** Convert `digits` to decimal and write the last 9 decimal digits to result.
** If `digits` contains additional digits, then those are silently ignored.
*/

void	ft_append_nine_digits(uint32_t digits, char *const result)
{
	uint32_t i;
	uint32_t c;

	if (digits == 0)
	{
		ft_memset(result, '0', 9);
		return ;
	}
	i = 0;
	while (i < 5)
	{
		c = MOD(digits, 10000);
		digits /= 10000;
		ft_memcpy(result + 7 - i, g_digit_tab + ((c % 100) << 1), 2);
		ft_memcpy(result + 5 - i, g_digit_tab + ((c / 100) << 1), 2);
		i += 4;
	}
	result[0] = (char)('0' + digits);
}
