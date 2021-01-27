/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpfx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:01:23 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/06 16:13:11 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

char	*ft_strpfx(const char *prefix, const char *str,
					int free_prefix, int free_str)
{
	size_t	prefix_len;
	size_t	str_len;
	char	*joined_str;

	joined_str = NULL;
	if (prefix == NULL)
		return ((char *)str);
	while (str != NULL)
	{
		prefix_len = ft_strlen(prefix);
		str_len = ft_strlen(str);
		if ((joined_str = malloc(prefix_len + str_len + 1)) == NULL)
			break ;
		joined_str[prefix_len + str_len] = '\0';
		while (str_len-- > 0)
			joined_str[prefix_len + str_len] = str[str_len];
		while (prefix_len-- > 0)
			joined_str[prefix_len] = prefix[prefix_len];
		break ;
	}
	if (free_prefix && prefix != NULL)
		free((char *)prefix);
	if (free_str && str != NULL)
		free((char *)str);
	return (joined_str);
}
