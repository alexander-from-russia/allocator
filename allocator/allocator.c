/*
 * allocator.c
 *
 *  Created on: Apr 11, 2023
 *      Author: alexander
 */

#include <stddef.h>
#include <stdint.h>
#include "allocator.h"
#include "compat.h"

ALLOCATOR_CREATE_MUTEX()

static uint8_t mem_pool[ALLOCATOR_POOL_SIZE];
static unsigned int mem_status_bitmap[ROUND_UP(ALLOCATOR_UNITS, BITS_IN_UNSIGNED_INT) /
				      BITS_IN_UNSIGNED_INT] = {0};

/**
 * \brief Allocate a memory buffer of fixed size
 * \return pointer to a newly allocated buf in success, NULL otherwise
 */
void *allocate_buf(void)
{
	size_t i;
	size_t buf_idx;
	unsigned int bit;
	void *ptr = NULL;

	if(!ALLOCATOR_TAKE_MUTEX()) {
		return NULL;
	}
	for (i = 0; i < ARRAY_SIZE(mem_status_bitmap); i++) {
		bit = ffs(~mem_status_bitmap[i]);
		if (bit) {
			bit--;
			buf_idx = i * BITS_IN_UNSIGNED_INT + bit;
			if (buf_idx >= ALLOCATOR_UNITS) {
				break;
			}
			mem_status_bitmap[i] |= 1 << bit;
			ptr = &mem_pool[buf_idx * ALLOCATOR_UNIT_SIZE];
			break;
		}
	}
	ALLOCATOR_RELEASE_MUTEX();

	return ptr;
}

/**
 * \brief Deallocate memory buffer
 * \param [in] *ptr - pointer to memory buf to deallocate
 * \return 0 - on success, error code otherwise
 */
int deallocate_buf(void *ptr)
{
	size_t offset = (size_t)ptr - (size_t)&mem_pool[0];
	size_t idx;
	unsigned int bit;

	if (offset >= ALLOCATOR_POOL_SIZE)
		return -1;
	if ((offset / ALLOCATOR_UNIT_SIZE) * ALLOCATOR_UNIT_SIZE != offset)
		return -1;

	bit = offset / ALLOCATOR_UNIT_SIZE;
	idx = bit / BITS_IN_UNSIGNED_INT;
	bit -= idx * BITS_IN_UNSIGNED_INT;
	if(!ALLOCATOR_TAKE_MUTEX()) {
		return -1;
	}
	mem_status_bitmap[idx] &= ~(1 << bit);
	ALLOCATOR_RELEASE_MUTEX();

	return 0;
}
