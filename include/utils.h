/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:53:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/11 17:39:29 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <sys/types.h>
# include <unistd.h>

# include "common.h"

void			*ft_memset(void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *s);
char			*ft_strpfx(const char *prefix, const char *str,
							int free_prefix, int free_str);
ssize_t			ft_write(int fd, const void *buf, size_t count);

typedef enum	e_sign_presentation
{
	SIGN_PRESENTATION_MINUS_ONLY,
	SIGN_PRESENTATION_MINUS_PLUS,
	SIGN_PRESENTATION_MINUS_SPACE,
}				t_sign_presentation;

typedef struct	s_int_format_options
{
	int					base;
	int					min_digits;
	int					use_uppercase;
	t_sign_presentation	sp;
}				t_int_format_options;

# define NULL_POINTER	"(nil)"
# define NULL_STRING	"(null)"

char			*ft_lli_base(t_max n, int base, int use_uppercase);
char			*ft_llu_base(t_umax n, int base, int use_uppercase);
char			*ft_format_lli(t_max n, t_int_format_options o);
char			*ft_format_llu(t_umax n, t_int_format_options o);
char			*ft_format_pointer(void *p, int min_digits);

typedef enum	e_size
{
	SIZE_HH,
	SIZE_H,
	SIZE_DEFAULT,
	SIZE_L,
	SIZE_LL,
	SIZE_Z,
	SIZE_T,
	SIZE_J
}				t_size;

t_max			ft_get_signed_va_arg(va_list *arg_ptr, t_size type);
t_umax			ft_get_unsigned_va_arg(va_list *arg_ptr, t_size type);

#endif
