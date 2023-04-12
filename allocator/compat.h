/*
 * compat.h
 *
 *  Created on: Apr 11, 2023
 *      Author: alexander
 */

#ifndef ALLOCATOR_COMPAT_H_
#define ALLOCATOR_COMPAT_H_

#define BITS_IN_UNSIGNED_INT	(sizeof(unsigned int) * 8)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


static inline int ffs(unsigned int x)
{
	int r = 1;

	if (!x)
		return 0;

	if (BITS_IN_UNSIGNED_INT == 64) {
		if (!(x & 0xffffffff)) {
			x = (uint64_t)x >> 32;
			r += 32;
		}
	}

	if (BITS_IN_UNSIGNED_INT >= 32) {
		if (!(x & 0xffff)) {
			x >>= 16;
			r += 16;
		}
	}

	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}
	if (!(x & 1)) {
		x >>= 1;
		r += 1;
	}
	return r;
}

#endif /* ALLOCATOR_COMPAT_H_ */
