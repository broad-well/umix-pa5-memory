// System calls to implement
#include <stddef.h>

// In this assignment, assume that there is 1 MB of physical memory.
#define PHYSICAL_MEMSIZE (1 << 20)

// The simulated physical memory begins at memstart and has a size of
// PHYSICAL_MEMSIZE.
extern void *memstart;

// Simulated memory pointer
typedef struct ptr {
  size_t offset;
} ptr_t;

// Allocate at least `bytes` bytes for reading and writing.
ptr_t NextFitAlloc(size_t bytes);

// Deallocate the block pointed to by `alloc`.
void NextFitFree(ptr_t alloc);

// Allocate a copy of the block pointed to by `alloc`.
// This function is useful in the implementation of `Fork()`.
ptr_t NextFitCopy(ptr_t alloc);
