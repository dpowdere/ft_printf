/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_ll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:54:30 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/04 16:55:00 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "utils.h"

#define ALWAYS_NON_NEGATIVE 0

static void		ft_fill_non_negative(t_sign_presentation sp, char *s1, char *s2)
{
	size_t	i;
	size_t	size1;
	size_t	size2;

	size1 = sizeof(s1);
	size2 = sizeof(s2);
	i = 0;
	if (sp == SIGN_PRESENTATION_MINUS_SPACE)
		s2[i++] = ' ';
	else if (sp == SIGN_PRESENTATION_MINUS_PLUS)
		s2[i++] = '+';
	while (i < size2)
	{
		if (i < size2 - size1)
			s2[i] = '0';
		else
			s2[i] = s1[i - (size2 - size1)];
		++i;
	}
	s2[i] = '\0';
}

static void		ft_fill_negative(char *s1, char *s2)
{
	size_t	i;
	size_t	size1;
	size_t	size2;

	size1 = sizeof(s1);
	size2 = sizeof(s2);
	s2[0] = '-';
	i = 1;
	while (i < size2)
	{
		if (i < size2 - size1 + 1)
			s2[i] = '0';
		else
			s2[i] = s1[i - (size2 - size1 + 1)];
		++i;
	}
	s2[i] = '\0';
}

static size_t	ft_augmented_size(size_t size, int min_digits,
					t_sign_presentation sp, int is_negative)
{
	size_t augmented_size;

	if (is_negative && size < (size_t)min_digits + 1)
		augmented_size = (size_t)min_digits + 1;
	else if (!is_negative && size < (size_t)min_digits)
		augmented_size = (size_t)min_digits;
	else
		augmented_size = size;
	if (!is_negative && sp != SIGN_PRESENTATION_MINUS_ONLY)
		augmented_size += 1;
	return (augmented_size);
}

char			*ft_format_lli(long long int n, t_int_format_options o)
{
	char	*s1;
	char	*s2;
	size_t	size1;
	size_t	size2;
	int		is_negative;

	if ((s1 = ft_lli_base(n, o.base, o.use_uppercase)) == NULL)
		return (NULL);
	is_negative = (n < 0);
	size1 = ft_strlen(s1);
	if ((!is_negative && (size_t)o.min_digits <= size1 &&
				o.sp == SIGN_PRESENTATION_MINUS_ONLY)
			|| (is_negative && (size_t)o.min_digits < size1))
		return (s1);
	size2 = ft_augmented_size(size1, o.min_digits, o.sp, is_negative);
	if ((s2 = malloc(size2 + 1)) == NULL)
		return (NULL);
	if (n < 0)
		ft_fill_negative(s1, s2);
	else
		ft_fill_non_negative(o.sp, s1, s2);
	free(s1);
	return (s2);
}

char			*ft_format_llu(unsigned long long int n, t_int_format_options o)
{
	char	*s1;
	char	*s2;
	size_t	size1;
	size_t	size2;

	if ((s1 = ft_llu_base(n, o.base, o.use_uppercase)) == NULL)
		return (NULL);
	size1 = ft_strlen(s1);
	if ((size_t)o.min_digits <= size1 && o.sp == SIGN_PRESENTATION_MINUS_ONLY)
		return (s1);
	size2 = ft_augmented_size(size1, o.min_digits, o.sp, ALWAYS_NON_NEGATIVE);
	if ((s2 = malloc(size2 + 1)) == NULL)
		return (NULL);
	ft_fill_non_negative(o.sp, s1, s2);
	free(s1);
	return (s2);
}
