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

#include "../libftprintf.h"

#define DONT_USE_UPPERCASE	0
#define DONT_FREE_PREFIX	0
#define DO_FREE_STRING		1

char	*ft_format_pointer(void *p, int min_digits)
{
	char					*s;
	t_int_format_options	opts;

	if (p == NULL)
		return (ft_strdup(NULL_POINTER));
	opts.base = 16;
	opts.min_digits = min_digits;
	opts.use_uppercase = DONT_USE_UPPERCASE;
	opts.sp = SIGN_PRESENTATION_MINUS_ONLY;
	s = ft_format_llu((unsigned long long int)p, opts);
	if (s == NULL)
		return (NULL);
	s = ft_strpfx("0x", s, DONT_FREE_PREFIX, DO_FREE_STRING);
	if (s == NULL)
		return (NULL);
	return (s);
}
