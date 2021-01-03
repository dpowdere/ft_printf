/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 16:44:57 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 17:47:57 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

# include "utils/utils.h"

# define STDOUT 1

# define PRINTF_NO_ERROR		0
# define PRINTF_WRITE_ERROR		-1
# define PRINTF_NOSPEC_ERROR	-2
# define PRINTF_MALLOC_ERROR	-4

struct s_spec;
struct s_toolbox;
typedef struct s_spec		t_spec;
typedef struct s_toolbox	t_toolbox;
typedef void				(*t_spec_ft)(t_toolbox *, va_list *);

#endif
