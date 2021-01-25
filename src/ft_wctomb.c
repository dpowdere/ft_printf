/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:46 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/25 18:52:29 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <wchar.h>

#include "libftprintf.h"

static inline void	ft___utf32_utf8_multibyte(char *s, wchar_t wc, int len)
{
	int		i;
	uint8_t	prefix;
	uint8_t	data_segm;
	uint8_t	data_mask;

	prefix = (uint8_t)~0u << (8 - len);
	data_segm = (uint8_t)(*(uint32_t *)&wc >> ((len - 1) * 6));
	data_mask = (uint8_t)~0u >> (len + 1);
	s[0] = (unsigned char)(prefix | (data_segm & data_mask));
	i = 1;
	while (i < len)
	{
		prefix = (uint8_t)0x80;
		data_segm = (uint8_t)(*(uint32_t *)&wc >> ((len - i - 1) * 6));
		data_mask = (uint8_t)0x3f;
		s[i] = (unsigned char)(prefix | (data_segm & data_mask));
		++i;
	}
}

/*
** A partial implementation of stdlib's `wctomb` function:
**
**  - The encoding of the `wc` wide char is always
**    considered to be UTF-32, thus a wrong result will
**    be produced on Windows with its UTF-16, as well
**    as on other non UTF-32 wide char platforms;
**
**  - The encoding of output string is always supposed
**    to be UTF-8;
**
**  - No special operation when `s` is NULL;
**
**  - No -1 return when a wide character cannot be
**    properly converted;
**
**  - From 1 to 6 UTF-8 bytes per unicode point according
**    to obsolete [RFC 2279](https://tools.ietf.org/html/rfc2279#page-4)
**    (sic!), not [RFC 3629](https://tools.ietf.org/html/rfc3629#page-4)
**    that requires no more than 4 bytes per unicode point.
*/

int					ft_wctomb(char *s, wchar_t wc)
{
	int len;

	len = ft_wctomb_len(wc);
	if (len == 1)
		*s = (unsigned char)wc;
	else
		ft___utf32_utf8_multibyte(s, wc, len);
	return (len);
}
