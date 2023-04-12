/*
 * allocator.h
 *
 *  Created on: Apr 11, 2023
 *      Author: alexander
 */

#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define ALLOCATOR_UNIT_SIZE		64
#define ALLOCATOR_UNITS			512
#define ALLOCATOR_POOL_SIZE		(ALLOCATOR_UNIT_SIZE * ALLOCATOR_UNITS)

#define ALLOCATOR_CREATE_MUTEX()
#define ALLOCATOR_TAKE_MUTEX()	true
#define ALLOCATOR_RELEASE_MUTEX()

void *allocate_buf(void);
int deallocate_buf(void *ptr);

#endif /* ALLOCATOR_H_ */
