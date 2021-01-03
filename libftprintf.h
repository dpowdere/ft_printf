/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:35:15 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 17:34:06 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "common.h"
# include "specs/specs.h"

typedef struct	s_toolbox
{
	const char	*cursor;
	const char	*fragment_start;
	int			cumulative_size;
	int			error;
	t_spec		spec;
	t_spec_ft	(*handlers)[SPEC_COUNT];
}				t_toolbox;

typedef enum	e_reset_type
{
	INIT_TOOLBOX,
	RESET_SPEC_INFO
}				t_reset_type;

int				ft_printf(const char *format, ...);
void			ft_print_field(char *str, size_t strsize, t_toolbox *toolbox);

#endif
