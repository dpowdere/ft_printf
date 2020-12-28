/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:35:15 by dpowdere          #+#    #+#             */
/*   Updated: 2020/12/28 18:23:04 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# define STDOUT 1

# define PRINTF_WRITE_ERROR	-1

# define FOUND			1
# define NOT_FOUND		0
# define FIND_ERROR		-1

int	ft_printf(const char *format, ...);

#endif
