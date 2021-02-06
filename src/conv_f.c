/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:48:37 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 16:28:21 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

static inline t_float_format_options	ft_get_float_opts(t_spec spec)
{
	t_float_format_options	opts;

	opts.output_type = FLOAT_FIXED;
	opts.precision = spec.precision;
	opts.flags = spec.flags;
	if (spec.precision == UNSPECIFIED)
		opts.precision = 6;
	return (opts);
}

static inline char						*ft_get_padded_num(double n,
													char *s,
													size_t len,
													t_toolbox *toolbox)
{
	size_t	diff;
	size_t	i;
	size_t	j;
	char	*zero_padded;

	i = 0;
	j = 0;
	diff = toolbox->spec.width - len;
	if ((zero_padded = malloc(toolbox->spec.width + 1)) == NULL)
		return (NULL);
	if (n < 0 ||
			toolbox->spec.flags & (FLAG_SHOW_PLUS | FLAG_SHOW_SPACE_PLUS))
		zero_padded[i++] = s[j++];
	while (diff-- > 0)
		zero_padded[i++] = '0';
	while (s[j])
		zero_padded[i++] = s[j++];
	zero_padded[i] = '\0';
	return (zero_padded);
}

static inline char						*ft_zero_pad(double n, char *s,
													t_toolbox *toolbox)
{
	size_t	len;
	char	*zero_padded;

	if (s == NULL)
		return (NULL);
	zero_padded = s;
	len = ft_strlen(s);
	if (toolbox->spec.flags & FLAG_ZERO_PAD && toolbox->spec.width >= 0
			&& len < (size_t)toolbox->spec.width && !ft_is_nan_or_infinity(n))
	{
		zero_padded = ft_get_padded_num(n, s, len, toolbox);
		free(s);
		if (zero_padded == NULL)
			return (NULL);
	}
	return (zero_padded);
}

void									ft_conv_f(t_toolbox *toolbox,
													va_list *arg_ptr)
{
	t_float_format_options	opts;
	size_t					typing_width;
	double					n;
	char					*s;

	n = va_arg(*arg_ptr, double);
	opts = ft_get_float_opts(toolbox->spec);
	s = ft_dtoa(n, &opts);
	s = ft_zero_pad(n, s, toolbox);
	if (s == NULL)
	{
		toolbox->error = PRINTF_MALLOC_ERROR;
		return ;
	}
	typing_width = ft_strlen(s);
	ft_print_field(s, typing_width, toolbox);
	free(s);
}
