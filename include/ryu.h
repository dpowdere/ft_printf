/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:20:30 by dpowdere          #+#    #+#             */
/*   Updated: 2021/02/06 18:20:36 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** A reproduction of Ulf Adams' Ryu algorithm for fast and accurate
** float-to-string conversion. See:
**
**   - Ulf Adams. 2018. Ryu: fast float-to-string conversion // SIGPLAN Not.
**     53, 4 (April 2018), 270–282. DOI:https://doi.org/10.1145/3296979.3192369
**
**   - Ulf Adams. 2019. Ryu revisited: printf floating point conversion //
**     Proc. ACM Program. Lang. 3, OOPSLA, Article 169 (October 2019), 23
**     pages. DOI:https://doi.org/10.1145/3360595
**
**   - https://doi.org/10.5281/zenodo.3366212
**
**   - https://github.com/ulfjack/ryu
**
** The implementation is a stripped-down version of the original
** C-implementation from https://github.com/ulfjack/ryu, slightly tweaked
** and reworked to count for `#`, `+` and ` ` printf flags and to comply with
** norminette's v2.0.2 requirements.
*/

#ifndef RYU_H
# define RYU_H

# include <stdint.h>

# include "aux.h"

char				*ft_dtoa(double d, t_float_format_options *opts);
int					ft_dtoa_get_exp(double d, t_float_format_options *opts);

# define DBL_EXP_MALLOC_ERROR	-1024

# define DBL_MANTISSA_BITS		52
# define DBL_EXPONENT_BITS		11
# define DBL_SIGN_BIT_SHIFT		(DBL_MANTISSA_BITS + DBL_EXPONENT_BITS)
# define DBL_BIAS				1023

# define POW10_ADDITIONAL_BITS	120
# define POW10_BITS4IX(ix)		((uint32_t)(16 * (ix) + POW10_ADDITIONAL_BITS))

typedef enum		e_roundup
{
	ROUNDUP_NEVER,
	ROUNDUP_UNCONDITIONALLY,
	ROUNDUP_IF_ODD
}					t_roundup;

struct				s_result
{
	char	*result;
	int		ix;
};

typedef struct		s_decomposed_dbl
{
	int32_t					e;
	uint64_t				m;
	t_float_format_options	*opts;
	t_roundup				roundup;
	uint32_t				frac_blocks;
	int						show_dot;
	int32_t					exp;
	uint32_t				digits;
	uint32_t				available_digits;
	uint32_t				printed_digits;
}					t_decomposed_dbl;

/*
** Returns uint32_t floor(log_10(2^e)); requires 0 <= e <= 1650.
**
** The first value this approximation fails for is 2^1651
** which is just greater than 10^297.
*/
# define LOG10_POW2(e)	(((uint32_t)(e) * 78913) >> 18)

/*
** https://bugs.llvm.org/show_bug.cgi?id=38217
*/
# ifdef __clang__
#  define MOD(x, y)	((x) - (y) * ((x) / (y)))
# else
#  define MOD(x, y)	((x) % (y))
# endif

# define D1E9 1000000000
# define MOD1E9(x)	(MOD((x), D1E9))

/*
** Returns true if value is divisible by 2^p.
** ((uint64_t)value != 0)
** ((uint32_t)p < 64)
*/
# define IS_DIV_POW2(v, p)	(((v) & ((1ull << (uint32_t)(p)) - 1)) == 0)

/*
** Index for exponent
*/
# define IX4EXP(e)	(((uint32_t)(e) + 15) / 16)

/*
** Length for index
** +1 for ceil, +16 for mantissa, +8 to round up when dividing by 9
*/
# define LEN4IX(ix) ((LOG10_POW2(16 * (int32_t)ix) + 1 + 16 + 8) / 9)

int					ft_append_n_digits(const uint32_t count,
							uint32_t digits, char *const s, int ix);
int					ft_append_d_digits(const uint32_t count,
							uint32_t digits, char *const s, int ix);
int					ft_append_c_digits(const uint32_t count,
							uint32_t digits, char *const s, int ix);
int					ft_append_nine_digits(uint32_t digits,
							char *const s, int ix);
int					ft_is_div_pow5(uint64_t value, uint32_t p);
int					ft_is_nan_or_infinity(double n);
int					ft_is_zero(double n);
int					ft_format_e_case1(t_decomposed_dbl *d,
							char *const s, int ix);
int					ft_format_e_case2(t_decomposed_dbl *d,
							char *const s, int ix);
int					ft_format_e_case3(t_decomposed_dbl *d,
							char *const s, int ix);
int					ft_format_e_exp(t_decomposed_dbl *d,
							char *const s, int ix);
int					ft_format_f_frac(t_decomposed_dbl *d,
							char *const s, int ix);
int					ft_format_f_int(t_decomposed_dbl d, char *const s, int ix);
int					ft_fill_zeros(int count, char *const s, int ix);
int					ft_format_sign(double n,
							t_float_format_options *opts, char *const s);
int					ft_roundup_e(t_decomposed_dbl *d, char *const s, int ix);
int					ft_roundup_f(t_decomposed_dbl *d, char *const s, int ix);

uint32_t			ft_decimal_len9(const uint32_t v);
uint32_t			ft_mul_shift_mod1e9(const uint64_t m,
							const uint64_t *const mul, const int32_t j);
uint64_t			ft_umul128(const uint64_t a, const uint64_t b,
							uint64_t *const product_hi);

char				*ft_dtoa_malloc(t_float_format_options *opts);
char				*ft_format_e(t_decomposed_dbl d, char *const s, int ix);
char				*ft_format_f(t_decomposed_dbl d, char *const s, int ix);
char				*ft_format_nan_or_infinity(double n,
							t_float_format_options *opts,
							char *const s, int ix);
char				*ft_format_zero(t_float_format_options *opts,
							char *const s, int ix);

t_decomposed_dbl	ft_decompose_dbl(double n, t_float_format_options *opts);

#endif
