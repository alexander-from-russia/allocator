/*
 * allocatorTEST.c
 *
 *  Created on: Apr 11, 2023
 *      Author: alexander
 */

#include <stddef.h>
#include <stdint.h>
#include <criterion/criterion.h>
#include "allocator.h"

static void *ptr[ALLOCATOR_UNITS];

/**
 * \brief Basic test cases for memory allocation
 */
Test(allocatorTEST, create) {
	size_t i;
	void *extra_ptr;
	int res;

	/* Try to take all chunks of memory */
	for (i = 0; i < ALLOCATOR_UNITS; i++) {
		ptr[i] = allocate_buf();
		cr_expect(ptr[i], "Allocation error 0");
	}
	/* Try to allocate memory buffer when memory pool is depleted, NULL should be returned */
	extra_ptr = allocate_buf();
	cr_expect(!extra_ptr, "Allocation error 1");
	/* Try to deallocate with invalid pointer, error code should be returned */
	res = deallocate_buf((void *)((size_t)ptr[0] + 1));
	cr_expect(res, "Allocation error 2");
	/* Release all allocated buffers */
	for (i = 0; i < ALLOCATOR_UNITS; i++) {
		res = deallocate_buf(ptr[i]);
		cr_expect(!res, "Allocation error 3");
	}
	/* Try to take all chunks of memory again */
	for (i = 0; i < ALLOCATOR_UNITS; i++) {
		ptr[i] = allocate_buf();
		cr_expect(ptr[i], "Allocation error 4");
	}
	/* Try to allocate memory buffer when memory pool is depleted, NULL should be returned */
	extra_ptr = allocate_buf();
	cr_expect(!extra_ptr, "Allocation error 5");
}
