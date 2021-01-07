/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:05:07 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 16:50:09 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECS_H
# define SPECS_H

# include "common.h"

# define SPEC_START_MARKER '%'

# define S(x)	ft_spec_ ## x
# define ft_spec_d	ft_spec_i

void						ft_spec_c(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_i(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_p(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_percent(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_s(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_u(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_upper_x(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_x(t_toolbox *t, va_list *arg_ptr);

# define NUM_SPECIRIERS	"iudXxp"
# define SPECIFIERS		"sciudXxp%"
# define SPEC_COUNT		9
# define STR_HDLRS		S(s), S(c)
# define INT_HDLRS		S(i), S(u), S(d), S(upper_x), S(x)
# define OTHER_HDLRS	S(p), S(percent)
# define SPEC_HANDLERS	{ STR_HDLRS, INT_HDLRS, OTHER_HDLRS }

# define FLAG_SPECIFIERS "-0"

typedef struct				s_spec
{
	char			specifier;
	int				size;
	int				width;
	int				precision;
	unsigned int	left_justify: 1;
	unsigned int	zero_pad: 1;
}							t_spec;

# define UNDEFINED					-1

# define YET_NO_SPEC				'\0'
# define DEFAULT_MIN_FIELD_WIDTH	0
# define DEFAULT_PRECISION			UNDEFINED
# define TAKE_FROM_ARG				-2

# define YES	1u
# define NO		0u

#endif
