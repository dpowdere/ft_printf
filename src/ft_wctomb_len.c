/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:41:27 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/25 17:55:42 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <wchar.h>

/*
** Calculate the length of the UTF-32 encoded wide char,
** when converted to UTF-8.
**
**  - The encoding of the `wc` wide char is always
**    considered to be UTF-32, thus a wrong result will
**    be produced on Windows with its UTF-16, as well
**    as on other non UTF-32 wide char platforms;
**
**  - The encoding of output string is always supposed
**    to be UTF-8;
**
**  - From 1 to 6 UTF-8 bytes per unicode point according
**    to obsolete [RFC 2279](https://tools.ietf.org/html/rfc2279#page-4)
**    (sic!), not [RFC 3629](https://tools.ietf.org/html/rfc3629#page-4)
**    that requires no more than 4 bytes per unicode point.
**
**  Cf. stdlib's `wctomb` function.
*/

int	ft_wctomb_len(wchar_t wc)
{
	uint32_t	n;
	int			len;

	n = *(uint32_t *)&wc;
	if (n <= 0x007f)
		len = 1;
	else if (n <= 0x07ff)
		len = 2;
	else if (n <= 0xffff)
		len = 3;
	else if (n <= 0x1fffff)
		len = 4;
	else if (n <= 0x3ffffff)
		len = 5;
	else
		len = 6;
	return (len);
}
