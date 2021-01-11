/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:28:42 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 18:37:37 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "common.h"

/*
** Parsing as stair climbing
*/
typedef void	(*t_stair_step)(t_toolbox *toolbox);

void			ft_parse_flags(t_toolbox *toolbox);
void			ft_parse_width(t_toolbox *toolbox);
void			ft_parse_precision(t_toolbox *toolbox);
void			ft_parse_size(t_toolbox *toolbox);
void			ft_parse_specifier(t_toolbox *toolbox);

# define P(x)	ft_parse_ ## x
# define STAIRS	{ P(flags), P(width), P(precision), P(size), P(specifier) }
# define STAIR_STEPS	5

/*
** Normalizing and accessing parsed data
*/
typedef enum	e_effector
{
	E_STRING_NULL,
	E_STRING_NON_NULL,
	E_POINTER_NULL,
	E_POINTER_NON_NULL,
	E_NUMBER_ZERO,
	E_NUMBER_POSITIVE,
	E_NUMBER_NEGATIVE
}				t_effector;
/*
** E_STRING_NULL		NULL pointer passed in as `char *` argument;
** E_STRING_NON_NULL	`char *` argument, being a valid (null-terminated)
**						or invalid (non null-terminated) C-string;
** E_POINTER_NULL		NULL pointer passed in as `void *` argument;
** E_POINTER_NOT_NULL	non NULL pointer passed in as `void *` argument;
** E_NUMBER_ZERO		0 passed in as %iduoXxEeFfGg parameter;
** E_NUMBER_POSITIVE	positive number passed in as any number type;
** E_NUMBER_NEGATIVE	negative number passed in as any signed number type
*/

void			ft_normalize_spec(t_spec *spec, va_list *arg_ptr);
size_t			ft_get_typing_width(t_spec *spec, char *s, t_effector t);

#endif
