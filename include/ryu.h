/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:20:30 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/18 15:53:27 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** A reproduction of Ulf Adams' Ryu algorithm for fast and accurate
** float-to-string conversion. See:
**
**   - Ulf Adams. 2018. Ryū: fast float-to-string conversion // SIGPLAN Not.
**     53, 4 (April 2018), 270–282. DOI:https://doi.org/10.1145/3296979.3192369
**
**   - Ulf Adams. 2019. Ryū revisited: printf floating point conversion //
**     Proc. ACM Program. Lang. 3, OOPSLA, Article 169 (October 2019), 23
**     pages. DOI:https://doi.org/10.1145/3360595
**
**   - https://doi.org/10.5281/zenodo.3366212
**
**   - https://github.com/ulfjack/ryu
**
** The implementation is a stripped-down version of the original
** C-implementation from https://github.com/ulfjack/ryu, slightly tweaked
** to count for `#`, `+` and ` ` printf flags.
*/

#ifndef RYU_H
# define RYU_H

# include <stdint.h>

# include "utils.h"

int		ft_dtoa_f(double d, uint32_t precision, char *result);
int		ft_dtoa_e(double d, uint32_t precision, char *result);

# define DOUBLE_MANTISSA_BITS 52
# define DOUBLE_EXPONENT_BITS 11
# define DOUBLE_BIAS 1023

# define POW10_ADDITIONAL_BITS 120
# define POW10_BITS4IX(ix)	((uint32_t)(16 * (ix) + POW10_ADDITIONAL_BITS))

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

uint32_t	ft_decimal_len9(const uint32_t v);
uint64_t	ft_double_to_bits(const double d);
uint64_t	ft_umul128(const uint64_t a,
						const uint64_t b,
						uint64_t *const product_hi);
uint32_t	ft_mul_shift_mod1e9(const uint64_t m,
								const uint64_t *const mul,
								const int32_t j);
int			ft_is_div_pow5(uint64_t value, uint32_t p);
void		ft_append_n_digits(const uint32_t olen,
								uint32_t digits,
								char *const result);
void		ft_append_d_digits(const uint32_t olen,
								uint32_t digits,
								char *const result);
void		ft_append_c_digits(const uint32_t count,
								uint32_t digits,
								char *const result);
void		ft_append_nine_digits(uint32_t digits, char *const result);
int			ft_copy_special_str_printf(char *const result,
										const int sign,
										const uint64_t mantissa);

#endif
