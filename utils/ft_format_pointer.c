/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 23:09:20 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/04 23:35:48 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "../libftprintf.h"

#define DONT_USE_UPPERCASE	0

char	*ft_format_pointer(void *p, int min_digits)
{
	char					*s1;
	char					*s2;
	size_t					len;
	t_int_format_options	opts;

	if (p == NULL)
		return (ft_strdup(NULL_POINTER));
	opts.base = 16;
	opts.min_digits = min_digits;
	opts.use_uppercase = DONT_USE_UPPERCASE;
	opts.sp = SIGN_PRESENTATION_MINUS_ONLY;
	s1 = ft_format_llu((unsigned long long int)p, opts);
	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	s2 = malloc(len + 2 + 1);
	if (s2 == NULL)
		return (NULL);
	s2[0] = '0';
	s2[1] = 'x';
	while (len-- > 0)
		s2[len + 3] = s1[len + 1];
	free(s1);
	return (s2);
}
