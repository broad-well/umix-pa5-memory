#pragma once
#include "hardware.h"
#include <ctype.h>

/**
 * Kernel-level functions in WEMIX
 */

#define MAXPROCS 16
#define MAXALLOCS 128
#define ALLOC_ALIGN 4

// ---------- Fragmentation ---------- //

/**
 * Use the first-fit policy to allocate a chunk of at least `bytes` bytes in the
 * `heap` variable declared in `hardware.h`. Return a pointer to the first byte
 * in the chunk. If there isn't a big enough hole, return NULL.
 *
 * Allocated blocks must always have a size that is divisible by ALLOC_ALIGN.
 * For example, if this function was called with bytes=2, it should find the
 * smallest multiple of 4 that is no smaller than 2. In this case, that would
 * result in a block of 4 bytes.
 *
 * Note: Please track your allocations outside the `heap` itself. Consider a
 * table of allocated entries. This is required for `FirstFitBytesFree` to be
 * correct.
 */
void *FirstFitAlloc(size_t bytes);

/**
 * Deallocate a chunk allocated using `FirstFitAlloc` in the `heap` variable
 * declared in `hardware.h`. Assume that the parameter `chunk` was previously
 * returned from `FirstFitAlloc`.
 */
void FirstFitFree(void *chunk);

/**
 * Return the total number of bytes allocated using `FirstFitAlloc`.
 */
size_t FirstFitBytesAllocated();

inline size_t FirstFitBytesFree() {
  return PHYSMEM_SIZE - FirstFitBytesAllocated();
}

/**
 * Return the number of holes between allocated blocks produced
 * by `FirstFitAlloc`.
 */
size_t FirstFitHoleCount();

// ---------- Buddy System ---------- //

/**
 * Same as FirstFitAlloc, but use the Buddy System from lecture instead.
 * Make sure to track the allocations separately from `heap` and separately from
 * the structures you use for FirstFit.
 *
 * Please use `PHYSMEM_SIZE` to assist with determining the size of each node in
 * your binary tree.
 */
void *BuddyAlloc(size_t bytes);

/**
 * Same as FirstFitFree, but expect a chunk allocated by BuddyAlloc instead.
 */
void BuddyFree(void *chunk);

/**
 * Return the total number of bytes allocated using `BuddyAlloc`.
 */
size_t BuddyBytesAllocated();

inline size_t BuddyBytesFree() {
  return PHYSMEM_SIZE - BuddyBytesAllocated();
}

/**
 * Return the number of holes between blocks allocated by `BuddyAlloc`.
 */
size_t BuddyHoleCount();
