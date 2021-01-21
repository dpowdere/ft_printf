/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:35:15 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/22 01:41:41 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "_aux.h"
# include "_ryu.h"
# include "_ryu_cache.h"

# define PRINTF_NO_ERROR		0
# define PRINTF_WRITE_ERROR		-1
# define PRINTF_PARSE_ERROR		-2
# define PRINTF_MALLOC_ERROR	-4

int	ft_printf(const char *format, ...);

#endif
