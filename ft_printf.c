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
#include <stddef.h>
#include <unistd.h>

#include "libftprintf.h"

static void	ft_reset(t_reset_type type, t_toolbox *toolbox)
{
	static t_func functions[SPEC_COUNT] = SPEC_HANDLERS;

	if (type == INIT_TOOLBOX)
	{
		toolbox->cumulative_size = 0;
		toolbox->error = PRINTF_NO_ERROR;
		toolbox->ft = &functions;
		toolbox->cursor = NULL;
	}
	toolbox->spec.specifier = YET_NO_SPEC;
	toolbox->spec.minimum_field_width = DEFAULT_MIN_FIELD_WIDTH;
	toolbox->spec.precision = DEFAULT_PRECISION;
	toolbox->spec.left_justify = NO;
	toolbox->spec.zero_pad = NO;
}

static void	ft_print_before_spec(const char **start, t_toolbox *toolbox)
{
	while (*toolbox->cursor && *toolbox->cursor != SPEC_START_MARKER)
		++toolbox->cursor;
	if (ft_write(STDOUT, *start, (size_t)(toolbox->cursor - *start)) < 0)
		toolbox->error = PRINTF_WRITE_ERROR;
	++toolbox->cursor;
	*start = toolbox->cursor;
}

static void	ft_parse_spec(const char **start, t_toolbox *toolbox)
{
	char *specifier;

	if (toolbox->error)
		return ;
	specifier = NULL;
	while (*toolbox->cursor &&
			(specifier = ft_strchr(SPECIFIERS, *toolbox->cursor)) == NULL)
		++toolbox->cursor;
	if (specifier == NULL)
	{
		toolbox->error = PRINTF_NOSPEC_ERROR;
		return ;
	}
	toolbox->spec.specifier = *specifier;
	if (*toolbox->cursor)
		++toolbox->cursor;
	*start = toolbox->cursor;
}

static void	ft_print_arg_by_spec(t_toolbox *toolbox, va_list *arg_ptr)
{
	int	i;

	if (toolbox->error)
		return ;
	if (toolbox->spec.minimum_field_width == TAKE_FROM_ARG)
		toolbox->spec.minimum_field_width = va_arg(*arg_ptr, int);
	if (toolbox->spec.precision == TAKE_FROM_ARG)
		toolbox->spec.precision = va_arg(*arg_ptr, int);
	i = 0;
	while (toolbox->spec.specifier != SPECIFIERS[i])
		++i;
	(*toolbox->ft)[i](toolbox, arg_ptr);
}

# define FRAGMENT_START format

int			ft_printf(const char *format, ...)
{
	va_list		arg_ptr;
	t_toolbox	toolbox;

	va_start(arg_ptr, format);
	ft_reset(INIT_TOOLBOX, &toolbox);
	toolbox.cursor = FRAGMENT_START;
	while (*toolbox.cursor && !toolbox.error)
	{
		ft_print_before_spec(&FRAGMENT_START, &toolbox);
		ft_parse_spec(&FRAGMENT_START, &toolbox);
		ft_print_arg_by_spec(&toolbox, &arg_ptr);
	}
	va_end(arg_ptr);
	return (toolbox.error ? toolbox.error : toolbox.cumulative_size);
}
