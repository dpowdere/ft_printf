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
** Convert `digits` to decimal and write the last `count` decimal digits to
** result. If `digits` contains additional digits, then those are silently
** ignored.
*/

void	ft_append_c_digits(const uint32_t count,
							uint32_t digits,
							char *const result)
{
	// Copy pairs of digits from g_digit_tab.
	uint32_t i = 0;
	for (; i < count - 1; i += 2)
	{
		const uint32_t c = (digits % 100) << 1;
		digits /= 100;
		ft_memcpy(result + count - i - 2, g_digit_tab + c, 2);
	}
	// Generate the last digit if count is odd.
	if (i < count)
	{
		const char c = (char)('0' + (digits % 10));
		result[count - i - 1] = c;
	}
}

/*
** Convert `digits` to decimal and write the last 9 decimal digits to result.
** If `digits` contains additional digits, then those are silently ignored.
*/

void	ft_append_nine_digits(uint32_t digits, char *const result)
{
	if (digits == 0)
	{
		ft_memset(result, '0', 9);
		return ;
	}
	for (uint32_t i = 0; i < 5; i += 4)
	{
		const uint32_t c = MOD(digits, 10000);
		digits /= 10000;
		const uint32_t c0 = (c % 100) << 1;
		const uint32_t c1 = (c / 100) << 1;
		ft_memcpy(result + 7 - i, g_digit_tab + c0, 2);
		ft_memcpy(result + 5 - i, g_digit_tab + c1, 2);
	}
	result[0] = (char)('0' + digits);
}

int		ft_copy_special_str_printf(char *const result,
									const int sign,
									const uint64_t mantissa)
{
	if (mantissa)
	{
		ft_memcpy(result, "nan", 3);
		return (3);
	}
	if (sign)
		result[0] = '-';
	ft_memcpy(result + sign, "Infinity", 8);
	return (sign + 8);
}
