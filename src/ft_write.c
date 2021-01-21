/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 20:42:42 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/02 20:52:47 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>

ssize_t	ft_write(int fd, const void *buf, size_t size)
{
	ssize_t	partial_size;

	while ((partial_size = write(fd, buf, size)) >= 0
			&& (size_t)partial_size < size)
	{
		buf = (unsigned char *)buf + partial_size;
		size -= partial_size;
	}
	return (partial_size);
}
