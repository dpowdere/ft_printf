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

void						ft_spec_c(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_d(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_e(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_f(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_g(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_i(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_n(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_o(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_p(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_percent(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_s(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_u(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_upper_e(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_upper_f(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_upper_g(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_upper_x(t_toolbox *t, va_list *arg_ptr);
void						ft_spec_x(t_toolbox *t, va_list *arg_ptr);

# define NUM_SPECIFIERS			"iduoXxEeFfGg" "p"
# define INT_SPECIFIERS			"iduoXx" "p"
# define UNSIGNED_SPECIFIERS	"uoXx"
# define SPECIFIERS				"sciduoXxEeFfGgpn%"
# define SPEC_COUNT				17

# define STR_HNDLRS		S(s), S(c)
# define SIGNED_HNDLRS	S(i), S(d)
# define UNSIGN_HNDLRS	S(u), S(o), S(upper_x), S(x)
# define FLOAT_HNDLRS	S(upper_e), S(e), S(upper_f), S(f), S(upper_g), S(g)
# define OTH_HNDLRS		S(p), S(n), S(percent)
# define INT_HNDLRS		SIGNED_HNDLRS, UNSIGN_HNDLRS
# define SPEC_HANDLERS	{ STR_HNDLRS, INT_HNDLRS, FLOAT_HNDLRS, OTH_HNDLRS }

# define FLAG_SPECIFIERS "-+ 0#"

typedef struct				s_spec
{
	char			specifier;
	t_size			size;
	int				width;
	int				precision;
	unsigned int	left_justify: 1;
	unsigned int	zero_pad: 1;
	unsigned int	field_width_zero_pad: 1;
	unsigned int	alternative_form: 1;
	unsigned int	show_plus: 1;
	unsigned int	show_space_plus: 1;
}							t_spec;

# define UNSPECIFIED	-1
# define TAKE_FROM_ARG	-2

# define YES	1u
# define NO		0u

#endif
