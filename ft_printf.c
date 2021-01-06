/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:02:35 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 18:37:08 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>

#include "libftprintf.h"

static void	ft_reset(t_reset_type type, t_toolbox *toolbox)
{
	static t_spec_ft handlers[SPEC_COUNT] = SPEC_HANDLERS;

	if (type == INIT_TOOLBOX)
	{
		toolbox->cumulative_size = 0;
		toolbox->error = PRINTF_NO_ERROR;
		toolbox->handlers = &handlers;
		toolbox->cursor = NULL;
	}
	toolbox->spec.specifier = YET_NO_SPEC;
	toolbox->spec.width = DEFAULT_MIN_FIELD_WIDTH;
	toolbox->spec.precision = DEFAULT_PRECISION;
	toolbox->spec.left_justify = NO;
	toolbox->spec.zero_pad = NO;
}

static void	ft_print_before_spec(t_toolbox *toolbox)
{
	const char *start;

	start = toolbox->cursor;
	while (*toolbox->cursor && *toolbox->cursor != SPEC_START_MARKER)
		++toolbox->cursor;
	if (ft_write(STDOUT, start, (size_t)(toolbox->cursor - start)) < 0)
		toolbox->error = PRINTF_WRITE_ERROR;
	toolbox->cumulative_size += toolbox->cursor - start;
	if (*toolbox->cursor == SPEC_START_MARKER)
		++toolbox->cursor;
}

static void	ft_parse_spec(t_toolbox *toolbox)
{
	static t_stair_step	parsing_stairs[STAIR_STEPS] = STAIRS;
	int					step;

	step = 0;
	while (step < STAIR_STEPS)
	{
		parsing_stairs[step++](toolbox);
		if (toolbox->error)
			return ;
	}
	if (*toolbox->cursor)
		++toolbox->cursor;
}

static void	ft_print_arg_by_spec(t_toolbox *toolbox, va_list *arg_ptr)
{
	int	i;

	if (toolbox->spec.width == TAKE_FROM_ARG)
		toolbox->spec.width = va_arg(*arg_ptr, int);
	if (toolbox->spec.precision == TAKE_FROM_ARG)
		toolbox->spec.precision = va_arg(*arg_ptr, int);
	ft_normalize_directives(toolbox);
	i = 0;
	while (toolbox->spec.specifier != SPECIFIERS[i])
		++i;
	(*toolbox->handlers)[i](toolbox, arg_ptr);
}

int			ft_printf(const char *format, ...)
{
	va_list		arg_ptr;
	t_toolbox	toolbox;

	va_start(arg_ptr, format);
	ft_reset(INIT_TOOLBOX, &toolbox);
	toolbox.cursor = format;
	while (*toolbox.cursor && !toolbox.error)
	{
		ft_print_before_spec(&toolbox);
		if (*toolbox.cursor && !toolbox.error)
		{
			ft_parse_spec(&toolbox);
			ft_print_arg_by_spec(&toolbox, &arg_ptr);
		}
		ft_reset(RESET_SPEC_INFO, &toolbox);
	}
	va_end(arg_ptr);
	return (toolbox.error ? toolbox.error : toolbox.cumulative_size);
}
