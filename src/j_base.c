/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_base.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:50:09 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/04 16:53:07 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "../include/utils.h"

#define LOWER_DIGITS "0123456789abcdefghijklmnopqrstuvwxyz"
#define UPPER_DIGITS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGITS	(use_upper_case ? UPPER_DIGITS : LOWER_DIGITS)

char	*ft_ji_base(t_max n, int base, int use_upper_case)
{
	t_max	power;
	t_max	i;
	int		digits;
	char	*s;

	digits = 1;
	power = 1;
	i = n;
	while ((i /= base) != 0)
	{
		power *= base;
		++digits;
	}
	if ((s = malloc(digits + (n < 0 ? 2 : 1))) == NULL)
		return (NULL);
	if (n < 0)
		s[i++] = '-';
	while (power != 0)
	{
		s[i++] = *((char *)DIGITS + (n / power * (n < 0 ? -1 : 1)));
		n %= power;
		power /= base;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_ju_base(t_umax n, int base, int use_upper_case)
{
	t_umax	power;
	t_umax	i;
	int		digits;
	char	*s;

	digits = 1;
	power = 1;
	i = n;
	while ((i /= base) != 0)
	{
		power *= base;
		++digits;
	}
	if ((s = malloc(digits + 1)) == NULL)
		return (NULL);
	while (power != 0)
	{
		s[i++] = *((char *)DIGITS + (n / power));
		n %= power;
		power /= base;
	}
	s[i] = '\0';
	return (s);
}
