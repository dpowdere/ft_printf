/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:17:34 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/04 23:31:26 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	extern int	errno;
	char		*dup;
	size_t		bufsize;

	if (!s)
		return (NULL);
	bufsize = 0;
	while (s[bufsize++])
		;
	dup = (char *)malloc(bufsize);
	if (!dup)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (bufsize-- > 0)
		dup[bufsize] = s[bufsize];
	return (dup);
}
