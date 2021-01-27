/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:32:07 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/21 22:34:31 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

#define ALWAYS_NON_NEGATIVE 0

static void		ft_fill_non_negative(t_sign_presentation sp,
								char *str, char *augmented_str,
								size_t augmented_size)
{
	size_t	i;
	size_t	basic_size;

	basic_size = ft_strlen(str);
	i = 0;
	if (sp == SIGN_PRESENTATION_MINUS_SPACE)
		augmented_str[i++] = ' ';
	else if (sp == SIGN_PRESENTATION_MINUS_PLUS)
		augmented_str[i++] = '+';
	while (i < augmented_size)
	{
		if (i < augmented_size - basic_size)
			augmented_str[i] = '0';
		else
			augmented_str[i] = str[i - (augmented_size - basic_size)];
		++i;
	}
	augmented_str[i] = '\0';
}

static void		ft_fill_negative(char *s, char *augmented_str,
								size_t basic_size, size_t augmented_size)
{
	size_t	i;

	augmented_str[0] = '-';
	i = 1;
	while (i < augmented_size)
	{
		if (i < augmented_size - basic_size + 1)
			augmented_str[i] = '0';
		else
			augmented_str[i] = s[i - (augmented_size - basic_size)];
		++i;
	}
	augmented_str[i] = '\0';
}

static size_t	ft_augmented_size(size_t basic_size, int min_digits,
					t_sign_presentation sp, int is_negative)
{
	size_t augmented_size;

	if (is_negative && basic_size < (size_t)min_digits + 1)
		augmented_size = (size_t)min_digits + 1;
	else if (!is_negative && basic_size < (size_t)min_digits)
		augmented_size = (size_t)min_digits;
	else
		augmented_size = basic_size;
	if (!is_negative && sp != SIGN_PRESENTATION_MINUS_ONLY)
		augmented_size += 1;
	return (augmented_size);
}

char			*ft_format_ji(t_max n, t_int_format_options o)
{
	char	*str;
	char	*augmented_str;
	size_t	basic_size;
	size_t	augmented_size;

	if ((str = ft_ji_base(n, o.base, o.use_uppercase)) == NULL)
		return (NULL);
	basic_size = ft_strlen(str);
	if ((n >= 0 && (size_t)o.min_digits <= basic_size &&
				o.sp == SIGN_PRESENTATION_MINUS_ONLY)
			|| (n < 0 && (size_t)o.min_digits < basic_size))
		return (str);
	augmented_size = ft_augmented_size(basic_size, o.min_digits, o.sp, n < 0);
	if ((augmented_str = malloc(augmented_size + 1)) == NULL)
	{
		free(str);
		return (NULL);
	}
	if (n < 0)
		ft_fill_negative(str, augmented_str, basic_size, augmented_size);
	else
		ft_fill_non_negative(o.sp, str, augmented_str, augmented_size);
	free(str);
	return (augmented_str);
}

char			*ft_format_ju(t_umax n, t_int_format_options o)
{
	char	*str;
	char	*augmented_str;
	size_t	basic_size;
	size_t	augmented_size;

	if ((str = ft_ju_base(n, o.base, o.use_uppercase)) == NULL)
		return (NULL);
	basic_size = ft_strlen(str);
	if ((size_t)o.min_digits <= basic_size
			&& o.sp == SIGN_PRESENTATION_MINUS_ONLY)
		return (str);
	augmented_size = ft_augmented_size(basic_size, o.min_digits,
										o.sp, ALWAYS_NON_NEGATIVE);
	if ((augmented_str = malloc(augmented_size + 1)) == NULL)
	{
		free(str);
		return (NULL);
	}
	ft_fill_non_negative(o.sp, str, augmented_str, augmented_size);
	free(str);
	return (augmented_str);
}
