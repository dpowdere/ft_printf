/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:16:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 18:42:40 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

static inline char	*ft_get_dtoa(double n,
								t_toolbox *toolbox,
								t_float_output output_type)
{
	t_float_format_options	opts;
	char					*s;

	opts.output_type = output_type;
	opts.precision = toolbox->spec.precision;
	opts.flags = toolbox->spec.flags;
	if (toolbox->spec.precision == UNSPECIFIED)
		opts.precision = 6;
	s = ft_dtoa(n, &opts);
	s = ft_float_zero_pad(s, n, toolbox);
	if (s == NULL)
		toolbox->error = PRINTF_MALLOC_ERROR;
	return (s);
}

static inline int	ft_get_exp(double n, t_toolbox *toolbox)
{
	t_float_format_options	opts;
	int						exp;

	if (toolbox->spec.precision == UNSPECIFIED)
		toolbox->spec.precision = 6;
	else if (toolbox->spec.precision == 0)
		toolbox->spec.precision = 1;
	opts.output_type = FLOAT_EXPONENTIAL;
	opts.precision = toolbox->spec.precision;
	opts.flags = toolbox->spec.flags;
	exp = ft_dtoa_get_exp(n, &opts);
	if (exp == DBL_EXP_MALLOC_ERROR)
		toolbox->error = PRINTF_MALLOC_ERROR;
	return (exp);
}

void				ft_conv_e(t_toolbox *toolbox, va_list *arg_ptr)
{
	double	n;
	char	*s;

	n = va_arg(*arg_ptr, double);
	if ((s = ft_get_dtoa(n, toolbox, FLOAT_EXPONENTIAL)) == NULL)
		return ;
	ft_print_field(s, ft_strlen(s), toolbox);
	free(s);
}

void				ft_conv_f(t_toolbox *toolbox, va_list *arg_ptr)
{
	double	n;
	char	*s;

	n = va_arg(*arg_ptr, double);
	if ((s = ft_get_dtoa(n, toolbox, FLOAT_FIXED)) == NULL)
		return ;
	ft_print_field(s, ft_strlen(s), toolbox);
	free(s);
}

void				ft_conv_g(t_toolbox *toolbox, va_list *arg_ptr)
{
	double	n;
	char	*s;
	int		exp;

	n = va_arg(*arg_ptr, double);
	if (ft_is_nan_or_infinity(n))
		s = ft_get_dtoa(n, toolbox, FLOAT_FIXED);
	else
	{
		if ((exp = ft_get_exp(n, toolbox)) == DBL_EXP_MALLOC_ERROR)
			return ;
		if (exp >= -4 && exp < toolbox->spec.precision)
		{
			toolbox->spec.precision -= exp + 1;
			s = ft_get_dtoa(n, toolbox, FLOAT_EXPONENTIAL);
		}
		else
		{
			toolbox->spec.precision -= 1;
			s = ft_get_dtoa(n, toolbox, FLOAT_FIXED);
		}
	}
	if (s == NULL)
		return ;
	ft_print_field(s, ft_strlen(s), toolbox);
	free(s);
}
