/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 01:22:28 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/28 15:02:17 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUX_H
# define AUX_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>
# include <wchar.h>

# ifndef ON_MACOS
#  define ON_MACOS 1
# endif

# define STDOUT 1

# define FLAG_SPECIFIERS	"-+ 0#"
# define SIZE_SPEC_CHARS	"hljzt"
# define INTRASPEC_CHARS	FLAG_SPECIFIERS "*.123456789" SIZE_SPEC_CHARS

# define SPEC_START_MARKER			'%'
# define NUM_CONV_SPECIFIERS		"iduoXxEeFfGg" "p"
# define INT_CONV_SPECIFIERS		"iduoXx" "p"
# if ON_MACOS
#  define UNSIGNED_CONV_SPECIFIERS	"uoXx" "p"
# else
#  define UNSIGNED_CONV_SPECIFIERS	"uoXx"
# endif
# define UPPERCASE_CONV_SPECIFIERS	"XEFG"
# define CONV_SPECIFIERS			"sciduoXxEeFfGgpn%"
# define CONV_SPEC_COUNT			17

# define C(x)			ft_conv_ ## x
# define STR_CONVS		C(s), C(c)
# define SIGNED_CONVS	C(i), C(d)
# define UNSIGN_CONVS	C(u), C(o), C(upper_x), C(x)
# define INT_CONVS		SIGNED_CONVS, UNSIGN_CONVS
# define FLOAT_CONVS	C(e), C(e), C(f), C(f), C(g), C(g)
# define OTHER_CONVS	C(p), C(n), C(percent)
# define CONVERTERS		{ STR_CONVS, INT_CONVS, FLOAT_CONVS, OTHER_CONVS }

# define FLT_INF_LOWER		"inf"
# define FLT_INF_UPPER		"INF"
# define FLT_EXP_LOWER		"e"
# define FLT_EXP_UPPER		"E"
# define FLT_EXP_ZERO		"+00"
# define FLT_EXP_ZERO_LOWER	(FLT_EXP_LOWER FLT_EXP_ZERO)
# define FLT_EXP_ZERO_UPPER	(FLT_EXP_UPPER FLT_EXP_ZERO)
# define FLT_NAN_LOWER		"nan"
# define FLT_NAN_UPPER		"NAN"
# define PTR_NULL			"(nil)"
# define STR_NULL			"(null)"

typedef intmax_t			t_max;
typedef uintmax_t			t_umax;

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

typedef enum				e_effector
{
	EFF_STRING_NULL,
	EFF_STRING_NON_NULL,
	EFF_POINTER_NULL,
	EFF_POINTER_NON_NULL,
	EFF_NUMBER_ZERO,
	EFF_NUMBER_POSITIVE,
	EFF_NUMBER_NEGATIVE
}							t_effector;
/*
** EFF_STRING_NULL		NULL pointer passed in as `char *` argument;
** EFF_STRING_NON_NULL	`char *` argument, being a valid (null-terminated)
**						or invalid (non null-terminated) C-string;
** EFF_POINTER_NULL		NULL pointer passed in as `void *` argument;
** EFF_POINTER_NOT_NULL	non NULL pointer passed in as `void *` argument;
** EFF_NUMBER_ZERO		0 passed in as %iduoXxEeFfGg parameter;
** EFF_NUMBER_POSITIVE	positive number passed in as any number type;
** EFF_NUMBER_NEGATIVE	negative number passed in as any signed number type
*/

typedef struct				s_spec
{
	char			conversion;
	t_size			size;
	int				width;
	int				precision;
	unsigned int	flags;
}							t_spec;

# define NO_FLAGS					00u
# define FLAG_LEFT_JUSTIFY			01u
# define FLAG_ZERO_PAD				02u
# define FLAG_FIELD_WIDTH_ZERO_PAD	04u
# define FLAG_ALTERNATIVE_FORM		010u
# define FLAG_SHOW_PLUS				020u
# define FLAG_SHOW_SPACE_PLUS		040u
# define FLAG_USE_UPPERCASE			0100u

# define UNSPECIFIED	-1
# define TAKE_FROM_ARG	-2

# define YES	1u
# define NO		0u

struct s_toolbox;
typedef void				(*t_converter)(struct s_toolbox *, va_list *);
typedef struct				s_toolbox
{
	const char		*cursor;
	int				error;
	int				cumulative_size;
	t_converter		(*converters)[CONV_SPEC_COUNT];
	t_spec			spec;
}							t_toolbox;

typedef enum				e_sign_presentation
{
	SIGN_PRESENTATION_MINUS_ONLY,
	SIGN_PRESENTATION_MINUS_PLUS,
	SIGN_PRESENTATION_MINUS_SPACE
}							t_sign_presentation;

typedef enum				e_float_output
{
	FLOAT_FIXED,
	FLOAT_EXPONENTIAL
}							t_float_output;

typedef struct				s_int_format_options
{
	int						base;
	int						min_digits;
	int						use_uppercase;
	t_sign_presentation		sp;
}							t_int_format_options;

typedef struct				s_float_format_options
{
	t_float_output			output_type;
	int						precision;
	unsigned int			flags;
}							t_float_format_options;

typedef enum				e_reset_type
{
	INIT_TOOLBOX,
	RESET_SPEC_INFO
}							t_reset_type;

void						ft_normalize_spec(t_spec *spec, va_list *arg_ptr);
size_t						ft_get_typing_width(t_spec *spec, char *s,
												t_effector t);

void						ft_parse_flags(t_toolbox *toolbox);
void						ft_parse_width(t_toolbox *toolbox);
void						ft_parse_precision(t_toolbox *toolbox);
void						ft_parse_size(t_toolbox *toolbox);
void						ft_parse_conversion(t_toolbox *toolbox);

void						ft_print_field(char *str, size_t strsize,
											t_toolbox *toolbox);

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

void						*ft_memcpy(void *dst, const void *src, size_t n);
void						*ft_memset(void *b, int c, size_t len);
char						*ft_strchr(const char *s, int c);
char						*ft_strdup(const char *s);
size_t						ft_strlen(const char *s);
char						*ft_strpfx(const char *prefix, const char *str,
										int free_prefix, int free_str);
size_t						ft_wcstombs(char *dst, const wchar_t *src,
										size_t n);
size_t						ft_wcstombs_len(const wchar_t *s);
int							ft_wctomb(char *s, wchar_t wc);
int							ft_wctomb_len(wchar_t wc);
ssize_t						ft_write(int fd, const void *buf, size_t count);

char						*ft_ji_base(t_max n, int base, int use_uppercase);
char						*ft_ju_base(t_umax n, int base, int use_uppercase);
char						*ft_format_ji(t_max n, t_int_format_options o);
char						*ft_format_ju(t_umax n, t_int_format_options o);
char						*ft_format_pointer(void *p, int min_digits);

t_max						ft_get_signed_va_arg(va_list *arg_ptr, t_size type);
t_umax						ft_get_unsigned_va_arg(va_list *arg_ptr,
													t_size type);

#endif
