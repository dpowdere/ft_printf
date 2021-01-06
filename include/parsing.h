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

typedef int	(*t_stair_step)(t_toolbox *toolbox);

int			ft_parse_flags(t_toolbox *toolbox);
int			ft_parse_width(t_toolbox *toolbox);
int			ft_parse_precision(t_toolbox *toolbox);
int			ft_parse_size(t_toolbox *toolbox);
int			ft_parse_specifier(t_toolbox *toolbox);

# define PARSING_SUCCESS	0
# define PARSING_FAIL		1

# define P(x)	ft_parse_ ## x

/*
** Parsing stairs
*/
# define STAIRS	{ P(flags), P(width), P(precision), P(size), P(specifier) }
# define STAIR_STEPS	5

#endif
