#ifndef RYU_COMMON_H
# define RYU_COMMON_H

# include <stdint.h>
# include <string.h>

/*
** Returns the number of decimal digits in v, which must not
** contain more than 9 digits.
**
** Function precondition: v is not a 10-digit number.
** (f2s: 9 digits are sufficient for round-tripping.)
** (d2fixed: We print 9-digit blocks.)
** (v < 1000000000)
*/
static inline uint32_t	decimalLength9(const uint32_t v)
{
	if (v >= 100000000)
		return (9);
	if (v >= 10000000)
		return (8);
	if (v >= 1000000)
		return (7);
	if (v >= 100000)
		return (6);
	if (v >= 10000)
		return (5);
	if (v >= 1000)
		return (4);
	if (v >= 100)
		return (3);
	if (v >= 10)
		return (2);
	return (1);
}

/*
** Returns floor(log_10(2^e)); requires 0 <= e <= 1650.
**
** The first value this approximation fails for is 2^1651
** which is just greater than 10^297.
** (0 <= e <= 1650)
*/
static inline uint32_t	log10Pow2(const int32_t e)
{
	return (((uint32_t)e * 78913) >> 18);
}

static inline int		copy_special_str(char * const result, const bool sign,
									const bool exponent, const bool mantissa)
{
	if (mantissa)
	{
		memcpy(result, "NaN", 3);
		return (3);
	}
	if (sign)
		result[0] = '-';
	if (exponent)
	{
		memcpy(result + sign, "Infinity", 8);
		return (sign + 8);
	}
	memcpy(result + sign, "0E0", 3);
	return (sign + 3);
}

static inline uint64_t	double_to_bits(const double d)
{
	uint64_t bits = 0;
	memcpy(&bits, &d, sizeof(double));
	return (bits);
}

#endif
