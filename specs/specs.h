/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:05:07 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 05:12:24 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECS_H
# define SPECS_H

# include <stdarg.h>

# define SPEC_START_MARKER '%'

typedef struct	s_toolbox	t_toolbox;
typedef void	(*t_func)(t_toolbox *, va_list *);

# define SPECIFIERS	"cs%"
# define SPEC_COUNT	3

void			ft_spec_c(t_toolbox *toolbox, va_list *arg_ptr);
void			ft_spec_s(t_toolbox *toolbox, va_list *arg_ptr);
void			ft_spec_percent(t_toolbox *toolbox, va_list *arg_ptr);

# define S(x)			ft_spec_ ## x
# define SPEC_HANDLERS	{ S(c), S(s), S(percent) }

typedef struct	s_spec
{
	char	specifier;
	int		minimum_field_width;
	int		precision;
	int		left_justify: 1;
	int		zero_pad: 1;
}				t_spec;

# define YET_NO_SPEC				'\0'
# define DEFAULT_MIN_FIELD_WIDTH	0
# define DEFAULT_PRECISION			-1
# define TAKE_FROM_ARG				-2

# define YES	1
# define NO		0

#endif
