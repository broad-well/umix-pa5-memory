#pragma once

/**
 * Functionalities provided by host hardware, such as address translation.
 */

#define PHYSMEM_SIZE 8192  // Pretend we're in the 1970s

extern char heap[PHYSMEM_SIZE];
