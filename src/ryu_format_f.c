/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu_format_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:18:21 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/27 00:20:30 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libftprintf.h"

static inline int		ft_fill_zeros(int count, char *const result, int index)
{
	ft_memset(result + index, '0', count);
	return (index + count);
}

int						ft_roundup_frac_without_exp(t_roundup roundup,
													char *const result,
													int index)
{
	int		round_index;
	int		dot_index;
	char	c;

	if (roundup != ROUNDUP_NEVER)
	{
		round_index = index;
		dot_index = 0;
		while (1)
		{
			--round_index;
			if (round_index == -1 || ((c = result[round_index]) == '-'))
			{
				result[round_index + 1] = '1';
				if (dot_index > 0)
				{
					result[dot_index] = '0';
					result[dot_index + 1] = '.';
				}
				result[index++] = '0';
				break ;
			}
			if (c == '.')
			{
				dot_index = round_index;
				continue ;
			}
			else if (c == '9')
			{
				result[round_index] = '0';
				roundup = ROUNDUP_UNCONDITIONALLY;
				continue ;
			}
			else
			{
				if (roundup == ROUNDUP_IF_ODD && c % 2 == 0)
					break ;
				result[round_index] = c + 1;
				break ;
			}
		}
	}
	return (index);
}

static inline uint32_t	ft_mshma(t_decomposed_dbl d,
								uint32_t p, int32_t tab_index)
{
	uint32_t digits;

	digits = ft_mul_shift_mod1e9(
		d.m << 8,
		g_pow10_split_2[p],
		ADDITIONAL_BITS_2 + (-d.e - 16 * tab_index) + 8);
	return (digits);
}

static inline int		ft_trailing_zeros(t_decomposed_dbl d,
										t_float_format_options *opts)
{
	int32_t	required_twos;
	int		trailing_zeros;

	required_twos = -d.e - (int32_t)opts->precision - 1;
	trailing_zeros = required_twos <= 0 ||
		(required_twos < 60 && IS_DIV_POW2(d.m, (uint32_t)required_twos));
	return (trailing_zeros);
}

int						ft_fill_non_zeros(t_decomposed_dbl d,
										t_float_format_options *opts,
										t_roundup *roundup,
										uint32_t digits,
										uint32_t i, uint32_t blocks,
										char *const result, int index)
{
	uint32_t maximum;
	uint32_t last_digit;
	uint32_t j;

	if (i < blocks - 1)
		index = ft_append_nine_digits(digits, result, index);
	else
	{
		maximum = opts->precision - 9 * i;
		last_digit = 0;
		j = 0;
		while (j++ < 9 - maximum)
		{
			last_digit = digits % 10;
			digits /= 10;
		}
		if (last_digit != 5)
			*roundup = last_digit > 5 ? ROUNDUP_UNCONDITIONALLY : ROUNDUP_NEVER;
		else
			*roundup = ft_trailing_zeros(d, opts) ?
				ROUNDUP_IF_ODD : ROUNDUP_UNCONDITIONALLY;
		if (maximum > 0)
			index = ft_append_c_digits(maximum, digits, result, index);
	}
	return (index);
}

int						ft_fill_blocks(t_decomposed_dbl d,
										t_float_format_options *opts,
										t_roundup *roundup,
										int32_t tab_index,
										uint32_t i, uint32_t blocks,
										char *const result, int index)
{
	uint32_t p;
	uint32_t digits;

	while (i < blocks)
	{
		p = g_pow10_offset_2[tab_index] + i - g_min_block_2[tab_index];
		if (p >= g_pow10_offset_2[tab_index + 1])
		{
			index = ft_fill_zeros(opts->precision - 9 * i, result, index);
			break ;
		}
		digits = ft_mshma(d, p, tab_index);
		index = ft_fill_non_zeros(d, opts, roundup, digits, i, blocks,
									result, index);
		if (i >= blocks - 1)
			break ;
		++i;
	}
	return (index);
}

int						ft_format_frac_without_exp(t_decomposed_dbl d,
							t_float_format_options *opts,
							char *const result, int index)
{
	t_roundup	roundup;
	int32_t		tab_index;
	uint32_t	blocks;
	uint32_t	i;

	roundup = ROUNDUP_NEVER;
	tab_index = -d.e / 16;
	blocks = opts->precision / 9 + 1;
	i = 0;
	if (blocks <= g_min_block_2[tab_index])
	{
		i = blocks;
		index = ft_fill_zeros(opts->precision, result, index);
	}
	else if (i < g_min_block_2[tab_index])
	{
		i = g_min_block_2[tab_index];
		index = ft_fill_zeros(9 * i, result, index);
	}
	index = ft_fill_blocks(d, opts, &roundup, tab_index, i, blocks,
							result, index);
	index = ft_roundup_frac_without_exp(roundup, result, index);
	return (index);
}

char					*ft_format_f(t_decomposed_dbl d,
										t_float_format_options *opts,
										char *const result, int index)
{
	index = ft_format_int_without_exp(d, result, index);
	if (opts->precision > 0 || opts->flags & FLAG_ALTERNATIVE_FORM)
		result[index++] = '.';
	if (d.e < 0)
		index = ft_format_frac_without_exp(d, opts, result, index);
	else
		index = ft_fill_zeros(opts->precision, result, index);
	return (result);
}
