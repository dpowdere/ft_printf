/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:45:52 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 16:47:38 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libftprintf.h"

static inline char			*ft_get_padded_num(double n,
											char *s, size_t len,
											t_toolbox *toolbox)
{
	size_t	diff;
	size_t	i;
	size_t	j;
	char	*zero_padded;

	i = 0;
	j = 0;
	diff = toolbox->spec.width - len;
	if ((zero_padded = malloc(toolbox->spec.width + 1)) == NULL)
		return (NULL);
	if (n < 0 ||
			toolbox->spec.flags & (FLAG_SHOW_PLUS | FLAG_SHOW_SPACE_PLUS))
		zero_padded[i++] = s[j++];
	while (diff-- > 0)
		zero_padded[i++] = '0';
	while (s[j])
		zero_padded[i++] = s[j++];
	zero_padded[i] = '\0';
	return (zero_padded);
}

char						*ft_float_zero_pad(char *s, double n,
												t_toolbox *toolbox)
{
	size_t	len;
	char	*zero_padded;

	if (s == NULL)
		return (NULL);
	zero_padded = s;
	len = ft_strlen(s);
	if (toolbox->spec.flags & FLAG_ZERO_PAD && toolbox->spec.width >= 0
			&& len < (size_t)toolbox->spec.width && !ft_is_nan_or_infinity(n))
	{
		zero_padded = ft_get_padded_num(n, s, len, toolbox);
		free(s);
		if (zero_padded == NULL)
			return (NULL);
	}
	return (zero_padded);
}
