/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:44 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/31 19:57:55 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

int		ft_format_e_exp(t_decomposed_dbl *d, char *const result, int index)
{
	if (d->opts->flags & FLAG_USE_UPPERCASE)
		result[index++] = *FLT_EXP_UPPER;
	else
		result[index++] = *FLT_EXP_LOWER;
	if (d->exp < 0)
	{
		result[index++] = '-';
		d->exp = -d->exp;
	}
	else
		result[index++] = '+';
	if (d->exp >= 100)
	{
		ft_memcpy(result + index, g_digit_tab + 2 * (d->exp / 10), 2);
		result[index + 2] = (char)('0' + d->exp % 10);
		index += 3;
	}
	else
	{
		ft_memcpy(result + index, g_digit_tab + 2 * d->exp, 2);
		index += 2;
	}
	return (index);
}

int		ft_case1(t_decomposed_dbl *d, char *const result, int index)
{
	uint32_t	idx;
	uint32_t	p10bits;
	int32_t		len;
	int32_t		i;

	idx = d->e < 0 ? 0 : IX4EXP((uint32_t)d->e);
	p10bits = POW10_BITS4IX(idx);
	len = (int32_t)LEN4IX(idx);
	i = len - 1;
	while (i >= 0)
	{
		d->digits = ft_mul_shift_mod1e9(
			d->m << 8,
			g_pow10_split[g_pow10_offset[idx] + i],
			(int32_t)((p10bits - d->e) + 8));
		if (d->printed_digits != 0)
		{
			if (d->printed_digits + 9 > (uint32_t)d->opts->precision)
			{
				d->available_digits = 9;
				break ;
			}
			index = ft_append_nine_digits(d->digits, result, index);
			d->printed_digits += 9;
		}
		else if (d->digits != 0)
		{
			d->available_digits = ft_decimal_len9(d->digits);
			d->exp = i * 9 + (int32_t)d->available_digits - 1;
			if (d->available_digits > (uint32_t)d->opts->precision)
				break ;
			if (d->show_dot)
				index = ft_append_d_digits(d->available_digits,
											d->digits, result, index);
			else
				result[index++] = (char)('0' + d->digits);
			d->printed_digits = d->available_digits;
			d->available_digits = 0;
		}
		--i;
	}
	return (index);
}

int		ft_case2(t_decomposed_dbl *d, char *const result, int index)
{
	int32_t		idx;
	int32_t		i;
	uint32_t	p;

	idx = -d->e / 16;
	i = g_min_block_2[idx];
	while (i < 200)
	{
		p = g_pow10_offset_2[idx] + (uint32_t)i - g_min_block_2[idx];
		d->digits = (p >= g_pow10_offset_2[idx + 1])
			? 0
			: ft_mul_shift_mod1e9(
				d->m << 8,
				g_pow10_split_2[p],
				ADDITIONAL_BITS_2 + (-d->e - 16 * idx) + 8);
		if (d->printed_digits != 0)
		{
			if (d->printed_digits + 9 > (uint32_t)d->opts->precision)
			{
				d->available_digits = 9;
				break ;
			}
			index = ft_append_nine_digits(d->digits, result, index);
			d->printed_digits += 9;
		}
		else if (d->digits != 0)
		{
			d->available_digits = ft_decimal_len9(d->digits);
			d->exp = -(i + 1) * 9 + (int32_t)d->available_digits - 1;
			if (d->available_digits > (uint32_t)d->opts->precision)
				break ;
			if (d->show_dot)
				index = ft_append_d_digits(d->available_digits, d->digits,
											result, index);
			else
				result[index++] = (char)('0' + d->digits);
			d->printed_digits = d->available_digits;
			d->available_digits = 0;
		}
		++i;
	}
	return (index);
}

int		ft_case3(t_decomposed_dbl *d, char *const result, int index)
{
	uint32_t maximum;
	uint32_t last_digit;
	uint32_t i;

	maximum = d->opts->precision - d->printed_digits;
	if (d->available_digits == 0)
		d->digits = 0;
	last_digit = 0;
	if (d->available_digits > maximum)
	{
		i = 0;
		while (i < d->available_digits - maximum)
		{
			last_digit = d->digits % 10;
			d->digits /= 10;
			++i;
		}
	}
	if (last_digit != 5)
		d->roundup = last_digit > 5 ? ROUNDUP_UNCONDITIONALLY : ROUNDUP_NEVER;
	else
	{
		/*
		** Is m * 2^d.e * 10^(precision + 1 - exp) integer?
		** precision was already increased by 1,
		** so we don't need to write + 1 here.
		*/
		const int32_t	rexp = (int32_t)d->opts->precision - d->exp;
		const int32_t	required_twos = -d->e - rexp;
		int				trailing_zeros;

		trailing_zeros = required_twos <= 0 ||
			(required_twos < 60 && IS_DIV_POW2(d->m, (uint32_t)required_twos));
		if (rexp < 0)
			trailing_zeros = trailing_zeros && ft_is_div_pow5(d->m, -rexp);
		d->roundup = trailing_zeros ? ROUNDUP_IF_ODD : ROUNDUP_UNCONDITIONALLY;
	}

	if (d->printed_digits != 0)
		index = ft_append_c_digits(maximum, d->digits, result, index);
	else
	{
		if (d->show_dot)
			index = ft_append_d_digits(maximum, d->digits, result, index);
		else
			result[index++] = (char)('0' + d->digits);
	}
	return (index);
}

char	*ft_format_e(t_decomposed_dbl d, char *const result, int index)
{
	++d.opts->precision;
	if (d.e >= -52)
		index = ft_case1(&d, result, index);
	if (d.e < 0 && d.available_digits == 0)
		index = ft_case2(&d, result, index);
	index = ft_case3(&d, result, index);
	index = ft_roundup_e(&d, result, index);
	index = ft_format_e_exp(&d, result, index);
	return (result);
}
