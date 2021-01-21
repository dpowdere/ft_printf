/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:35:15 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/03 17:34:06 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# ifndef DARWIN
#  define DARWIN 1
# endif

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>

# include "ryu.h"
# include "ryu_cache.h"

# define STDOUT 1

# define PRINTF_NO_ERROR		0
# define PRINTF_WRITE_ERROR		-1
# define PRINTF_PARSE_ERROR		-2
# define PRINTF_MALLOC_ERROR	-4

typedef enum				e_size
{
	SIZE_HH,
	SIZE_H,
	SIZE_DEFAULT,
	SIZE_L,
	SIZE_LL,
	SIZE_Z,
	SIZE_T,
	SIZE_J
}							t_size;

struct s_spec;
struct s_toolbox;
typedef struct s_spec		t_spec;
typedef struct s_toolbox	t_toolbox;

typedef void				(*t_spec_ft)(t_toolbox *, va_list *);

typedef intmax_t			t_max;
typedef uintmax_t			t_umax;

typedef enum				e_reset_type
{
	INIT_TOOLBOX,
	RESET_SPEC_INFO
}							t_reset_type;

int							ft_printf(const char *format, ...);
void						ft_print_field(char *str, size_t strsize,
											t_toolbox *toolbox);

/*
** Parsing as stair climbing
*/
typedef void	(*t_stair_step)(t_toolbox *toolbox);

void			ft_parse_flags(t_toolbox *toolbox);
void			ft_parse_width(t_toolbox *toolbox);
void			ft_parse_precision(t_toolbox *toolbox);
void			ft_parse_size(t_toolbox *toolbox);
void			ft_parse_conversion(t_toolbox *toolbox);

/*
** Normalizing and accessing parsed data
*/
typedef enum	e_effector
{
	E_STRING_NULL,
	E_STRING_NON_NULL,
	E_POINTER_NULL,
	E_POINTER_NON_NULL,
	E_NUMBER_ZERO,
	E_NUMBER_POSITIVE,
	E_NUMBER_NEGATIVE
}				t_effector;
/*
** E_STRING_NULL		NULL pointer passed in as `char *` argument;
** E_STRING_NON_NULL	`char *` argument, being a valid (null-terminated)
**						or invalid (non null-terminated) C-string;
** E_POINTER_NULL		NULL pointer passed in as `void *` argument;
** E_POINTER_NOT_NULL	non NULL pointer passed in as `void *` argument;
** E_NUMBER_ZERO		0 passed in as %iduoXxEeFfGg parameter;
** E_NUMBER_POSITIVE	positive number passed in as any number type;
** E_NUMBER_NEGATIVE	negative number passed in as any signed number type
*/

void			ft_normalize_spec(t_spec *spec, va_list *arg_ptr);
size_t			ft_get_typing_width(t_spec *spec, char *s, t_effector t);

# define SPEC_START_MARKER '%'

# define S(x)	ft_conv_ ## x

void						ft_conv_c(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_d(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_e(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_f(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_g(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_i(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_n(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_o(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_p(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_percent(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_s(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_u(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_upper_e(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_upper_f(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_upper_g(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_upper_x(t_toolbox *t, va_list *arg_ptr);
void						ft_conv_x(t_toolbox *t, va_list *arg_ptr);

# define NUM_SPECIFIERS			"iduoXxEeFfGg" "p"
# define INT_SPECIFIERS			"iduoXx" "p"
# define UNSIGNED_SPECIFIERS	"uoXx"
# define SPECIFIERS				"sciduoXxEeFfGgpn%"
# define SPEC_COUNT				17

# define STR_HNDLRS		S(s), S(c)
# define SIGNED_HNDLRS	S(i), S(d)
# define UNSIGN_HNDLRS	S(u), S(o), S(upper_x), S(x)
# define FLOAT_HNDLRS	S(upper_e), S(e), S(upper_f), S(f), S(upper_g), S(g)
# define OTHER_HNDLRS	S(p), S(n), S(percent)
# define INT_HNDLRS		SIGNED_HNDLRS, UNSIGN_HNDLRS
# define SPEC_HANDLERS	{ STR_HNDLRS, INT_HNDLRS, FLOAT_HNDLRS, OTHER_HNDLRS }

# define FLAG_SPECIFIERS	"-+ 0#"
# define SIZE_SPEC_CHARS	"hljzt"
# define INTRASPEC_CHARS	FLAG_SPECIFIERS ".123456789" SIZE_SPEC_CHARS

typedef struct				s_spec
{
	char			specifier;
	t_size			size;
	int				width;
	int				precision;
	unsigned int	left_justify: 1;
	unsigned int	zero_pad: 1;
	unsigned int	field_width_zero_pad: 1;
	unsigned int	alternative_form: 1;
	unsigned int	show_plus: 1;
	unsigned int	show_space_plus: 1;
}							t_spec;

# define UNSPECIFIED	-1
# define TAKE_FROM_ARG	-2

# define YES	1u
# define NO		0u

typedef struct	s_toolbox
{
	const char	*cursor;
	int			cumulative_size;
	int			error;
	t_spec		spec;
	t_spec_ft	(*handlers)[SPEC_COUNT];
}				t_toolbox;

void			*ft_memcpy(void *dst, const void *src, size_t n);
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

char			*ft_ji_base(t_max n, int base, int use_uppercase);
char			*ft_ju_base(t_umax n, int base, int use_uppercase);
char			*ft_format_ji(t_max n, t_int_format_options o);
char			*ft_format_ju(t_umax n, t_int_format_options o);
char			*ft_format_pointer(void *p, int min_digits);

t_max			ft_get_signed_va_arg(va_list *arg_ptr, t_size type);
t_umax			ft_get_unsigned_va_arg(va_list *arg_ptr, t_size type);

#endif
