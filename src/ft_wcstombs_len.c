/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:26:24 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/25 10:39:44 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

size_t	ft_wcstombs_len(const wchar_t *s)
{
	size_t		len;
	size_t		i;
	uint32_t	x;

	i = 0;
	len = 0;
	while (s[i] != L'\0')
	{
		x = *(uint32_t *)(s + i);
		if (x <= 0x007f)
			len += 1;
		else if (x <= 0x07ff)
			len += 2;
		else if (x <= 0xffff)
			len += 3;
		else if (x <= 0x1fffff)
			len += 4;
		else if (x <= 0x3ffffff)
			len += 5;
		else
			len += 6;
		++i;
	}
	return (len);
}
