/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:35:15 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 05:11:45 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

# include "utils/utils.h"
# include "specs/specs.h"

# define STDOUT 1

# define PRINTF_NO_ERROR		0
# define PRINTF_WRITE_ERROR		-1
# define PRINTF_NOSPEC_ERROR	-2

typedef struct	s_toolbox
{
	const char	*cursor;
	const char	*fragment_start;
	int			cumulative_size;
	int			error;
	t_spec		spec;
	t_func		(*ft)[SPEC_COUNT];
}				t_toolbox;

typedef enum	e_reset_type
{
	INIT_TOOLBOX,
	RESET_SPEC_INFO
}				t_reset_type;

int				ft_printf(const char *format, ...);

#endif
