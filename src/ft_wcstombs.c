/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:28:31 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/25 19:47:26 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <wchar.h>

#include "libftprintf.h"

/*
** A partial implementation of stdlib's `wcstombs` function:
**
**  - The encoding of the `src` wide char string is always
**    considered to be UTF-32, thus a wrong result will be
**    produced on Windows with its UTF-16, as well as on other
**    non UTF-32 wide char platforms;
**
**  - The encoding of `dst` output string is always supposed
**    to be UTF-8;
**
**  - No special operation when `dst` is NULL;
**
**  - No (size_t)-1 return when a wide character is
**    encountered which cannot be converted;
**
**  - From 1 to 6 UTF-8 bytes per unicode point according
**    to obsolete [RFC 2279](https://tools.ietf.org/html/rfc2279#page-4)
**    (sic!), not [RFC 3629](https://tools.ietf.org/html/rfc3629#page-4)
**    that requires no more than 4 bytes per unicode point.
*/

size_t	ft_wcstombs(char *dst, const wchar_t *src, size_t n)
{
	int		len;
	size_t	m;

	m = 0;
	while (*src != L'\0' && m + (size_t)ft_wctomb_len(*src) <= n)
	{
		len = ft_wctomb(dst, *src);
		m += (size_t)len;
		dst += len;
		src += 1;
	}
	if (m < n)
		*dst = '\0';
	return (m);
}
