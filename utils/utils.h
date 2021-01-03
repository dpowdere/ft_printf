/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:53:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/02 21:54:26 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <sys/types.h>
# include <unistd.h>

void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
ssize_t	ft_write(int fd, const void *buf, size_t count);

#endif
