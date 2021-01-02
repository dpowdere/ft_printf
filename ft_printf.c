/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:02:35 by dpowdere          #+#    #+#             */
/*   Updated: 2020/12/28 18:28:47 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "libftprintf.h"

int		ft_find_format_specifier(const char **start, int *total_size_or_error)
{
	const char	*cursor;
	int			size;
	int			partial_size;

	cursor = *start;
	while (*cursor && *cursor != '%')
		++cursor;
	size = (int)(cursor - *start);
	*total_size_or_error += size;
	while ((partial_size = write(STDOUT, *start, size)) < size
			&& partial_size >= 0)
	{
		*start = *start + partial_size;
		size -= partial_size;
	}
	if (partial_size < 0)
	{
		*total_size_or_error = PRINTF_WRITE_ERROR;
		return (FIND_ERROR);
	}
	*start = cursor;
	return (*cursor == '\0' ? NOT_FOUND : FOUND);
}

void	ft_parse_format_specifier(
			const char **start, int *total_size_or_error, va_list *arg_ptr)
{
	*start += 1;
	(void)total_size_or_error;
	(void)arg_ptr;
}

int		ft_printf(const char *format, ...)
{
	int			total_size_or_error;
	va_list		arg_ptr;

	total_size_or_error = 0;
	va_start(arg_ptr, format);
	while (ft_find_format_specifier(&format, &total_size_or_error) == FOUND)
		ft_parse_format_specifier(&format, &total_size_or_error, &arg_ptr);
	va_end(arg_ptr);
	return (total_size_or_error);
}
