#ifndef RYU_D2S_INTRINSICS_H
#define RYU_D2S_INTRINSICS_H

#include <stdint.h>

static inline uint64_t	umul128(const uint64_t a, const uint64_t b,
								uint64_t* const productHi)
{
	const uint32_t aLo = (uint32_t)a;
	const uint32_t aHi = (uint32_t)(a >> 32);
	const uint32_t bLo = (uint32_t)b;
	const uint32_t bHi = (uint32_t)(b >> 32);

	const uint64_t b00 = (uint64_t)aLo * bLo;
	const uint64_t b01 = (uint64_t)aLo * bHi;
	const uint64_t b10 = (uint64_t)aHi * bLo;
	const uint64_t b11 = (uint64_t)aHi * bHi;

	const uint32_t b00Lo = (uint32_t)b00;
	const uint32_t b00Hi = (uint32_t)(b00 >> 32);

	const uint64_t mid1 = b10 + b00Hi;
	const uint32_t mid1Lo = (uint32_t)(mid1);
	const uint32_t mid1Hi = (uint32_t)(mid1 >> 32);

	const uint64_t mid2 = b01 + mid1Lo;
	const uint32_t mid2Lo = (uint32_t)(mid2);
	const uint32_t mid2Hi = (uint32_t)(mid2 >> 32);

	const uint64_t pHi = b11 + mid1Hi + mid2Hi;
	const uint64_t pLo = ((uint64_t)mid2Lo << 32) | b00Lo;

	*productHi = pHi;
	return (pLo);
}

/*
** (0 < dist < 64);
*/
static inline uint64_t	shiftright128(const uint64_t lo, const uint64_t hi,
										const uint32_t dist)
{
	return ((hi << (64 - dist)) | (lo >> dist));
}

static inline uint64_t	div5(const uint64_t x)
{
	return (x / 5);
}

static inline uint64_t	div10(const uint64_t x)
{
	return (x / 10);
}

static inline uint64_t	div100(const uint64_t x)
{
	return (x / 100);
}

static inline uint64_t	div1e8(const uint64_t x)
{
	return (x / 100000000);
}

static inline uint64_t	div1e9(const uint64_t x)
{
	return (x / 1000000000);
}

static inline uint32_t	mod1e9(const uint64_t x)
{
	return ((uint32_t)(x - 1000000000 * div1e9(x)));
}

/*
** value != 0
*/
static inline uint32_t	pow5Factor(uint64_t value)
{
	uint32_t count = 0;

	while (true)
	{
		const uint64_t q = div5(value);
		const uint32_t r = ((uint32_t) value) - 5 * ((uint32_t) q);
		if (r != 0)
			break ;
		value = q;
		++count;
	}
	return (count);
}

// Returns true if value is divisible by 5^p.
static inline bool		multipleOfPowerOf5(const uint64_t value,
											const uint32_t p)
{
	return pow5Factor(value) >= p;
}

// Returns true if value is divisible by 2^p.
static inline bool		multipleOfPowerOf2(const uint64_t value,
											const uint32_t p)
{
	// (value != 0)
	// (p < 64)
	return ((value & ((1ull << p) - 1)) == 0);
}

// We need a 64x128-bit multiplication and a subsequent 128-bit shift.
// Multiplication:
//   The 64-bit factor is variable and passed in, the 128-bit factor comes
//   from a lookup table. We know that the 64-bit factor only has 55
//   significant bits (i.e., the 9 topmost bits are zeros). The 128-bit
//   factor only has 124 significant bits (i.e., the 4 topmost bits are
//   zeros).
// Shift:
//   In principle, the multiplication result requires 55 + 124 = 179 bits to
//   represent. However, we then shift this value to the right by j, which is
//   at least j >= 115, so the result is guaranteed to fit into 179 - 115 = 64
//   bits. This means that we only need the topmost 64 significant bits of
//   the 64x128-bit multiplication.
//
// There are several ways to do this:
// 1. Best case: the compiler exposes a 128-bit type.
//    We perform two 64x64-bit multiplications, add the higher 64 bits of the
//    lower result to the higher result, and shift by j - 64 bits.
//
//    We explicitly cast from 64-bit to 128-bit, so the compiler can tell
//    that these are only 64-bit inputs, and can map these to the best
//    possible sequence of assembly instructions.
//    x64 machines happen to have matching assembly instructions for
//    64x64-bit multiplications and 128-bit shifts.
//
// 2. Second best case: the compiler exposes intrinsics for the x64 assembly
//    instructions mentioned in 1.
//
// 3. We only have 64x64 bit instructions that return the lower 64 bits of
//    the result, i.e., we have to use plain C.
//    Our inputs are less than the full width, so we have three options:
//    a. Ignore this fact and just implement the intrinsics manually.
//    b. Split both into 31-bit pieces, which guarantees no internal overflow,
//       but requires extra work upfront (unless we change the lookup table).
//    c. Split only the first factor into 31-bit pieces, which also guarantees
//       no internal overflow, but requires extra work since the intermediate
//       results are not perfectly aligned.

static inline uint64_t	mulShift64(const uint64_t m, const uint64_t* const mul,
									const int32_t j)
{
	// m is maximum 55 bits
	uint64_t high1;                                   // 128
	const uint64_t low1 = umul128(m, mul[1], &high1); // 64
	uint64_t high0;                                   // 64
	umul128(m, mul[0], &high0);                       // 0
	const uint64_t sum = high0 + low1;
	if (sum < high0)
		++high1; // overflow into high1
	return shiftright128(sum, high1, j - 64);
}

// This is faster if we don't have a 64x64->128-bit multiplication.
static inline uint64_t	mulShiftAll64(uint64_t m, const uint64_t* const mul,
										const int32_t j, uint64_t* const vp,
										uint64_t* const vm,
										const uint32_t mmShift)
{
	m <<= 1;
	// m is maximum 55 bits
	uint64_t tmp;
	const uint64_t lo = umul128(m, mul[0], &tmp);
	uint64_t hi;
	const uint64_t mid = tmp + umul128(m, mul[1], &hi);
	hi += mid < tmp; // overflow into hi

	const uint64_t lo2 = lo + mul[0];
	const uint64_t mid2 = mid + mul[1] + (lo2 < lo);
	const uint64_t hi2 = hi + (mid2 < mid);
	*vp = shiftright128(mid2, hi2, (uint32_t) (j - 64 - 1));

	if (mmShift == 1)
	{
		const uint64_t lo3 = lo - mul[0];
		const uint64_t mid3 = mid - mul[1] - (lo3 > lo);
		const uint64_t hi3 = hi - (mid3 > mid);
		*vm = shiftright128(mid3, hi3, (uint32_t) (j - 64 - 1));
	}
	else
	{
		const uint64_t lo3 = lo + lo;
		const uint64_t mid3 = mid + mid + (lo3 < lo);
		const uint64_t hi3 = hi + hi + (mid3 < mid);
		const uint64_t lo4 = lo3 - mul[0];
		const uint64_t mid4 = mid3 - mul[1] - (lo4 > lo3);
		const uint64_t hi4 = hi3 - (mid4 > mid3);
		*vm = shiftright128(mid4, hi4, (uint32_t) (j - 64));
	}

	return (shiftright128(mid, hi, (uint32_t)(j - 64 - 1)));
}

#endif
