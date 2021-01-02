/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:35:15 by dpowdere          #+#    #+#             */
/*   Updated: 2020/12/29 18:55:05 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>

# include "utils/utils.h"

# define STDOUT 1

# define PRINTF_WRITE_ERROR	-1

# define FOUND			1
# define NOT_FOUND		0
# define FIND_ERROR		-1

typedef			void t_func(void);

# define SPECIFIERS	"cs"

void			ft_spec_c(void);
void			ft_spec_s(void);

typedef struct	s_spec_options
{
	int	left_justify: 1;
	int	zero_pad: 1;
}				t_spec_options;

int				ft_printf(const char *format, ...);

#endif
