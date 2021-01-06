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

char	*ft_strpfx(const char *prefix, const char *str,
					int free_prefix, int free_str)
{
	size_t	prefix_len;
	size_t	str_len;
	char	*joined_str;

	prefix_len = 0;
	while (prefix[prefix_len])
		++prefix_len;
	str_len = 0;
	while (str[str_len])
		++str_len;
	if ((joined_str = malloc(prefix_len + str_len + 1)) == NULL)
		return (NULL);
	joined_str[prefix_len + str_len] = '\0';
	while (str_len-- > 0)
		joined_str[prefix_len + str_len] = str[str_len];
	while (prefix_len-- > 0)
		joined_str[prefix_len] = prefix[prefix_len];
	if (free_prefix)
		free((char *)prefix);
	if (free_str)
		free((char *)str);
	return (joined_str);
}
