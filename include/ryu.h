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

int d2s_buffered_n(double f, char* result);
void d2s_buffered(double f, char* result);
char* d2s(double f);

int d2fixed_buffered_n(double d, uint32_t precision, char* result);
void d2fixed_buffered(double d, uint32_t precision, char* result);
char* d2fixed(double d, uint32_t precision);

int d2exp_buffered_n(double d, uint32_t precision, char* result);
void d2exp_buffered(double d, uint32_t precision, char* result);
char* d2exp(double d, uint32_t precision);

#endif
