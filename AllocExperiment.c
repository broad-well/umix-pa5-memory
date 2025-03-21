/* Memory allocation experiment runner ("user mode") */

#include "wemix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Test format
 * 
 * Each test consists of a sequence of allocation and deallocation operations.
 * Each allocation operation calls FirstFitAlloc or BuddyAlloc, and each
 * deallocation operation calls FirstFitFree or BuddyFree, depending on the test
 * mode. In the test file, each operation occupies exactly one line. Allocation
 * operations have the following format:
 *
 * ALLOC x
 *
 * where "x" is replaced with the number of bytes passed to FirstFitAlloc or
 * BuddyAlloc. Deallocation operations have the following format:
 *
 * FREE i
 *
 * which deallocates the chunk from the "i"th ALLOC operation, starting from 0.
 * For example, the following test file contents:
 *
 * ALLOC 24
 * ALLOC 14
 * FREE 0
 * ALLOC 8
 * FREE 2
 * FREE 1
 *
 * May be translated into the following calls, if the test is in Buddy System
 * mode:
 *
 * void *alloc0 = BuddyAlloc(24);
 * void *alloc1 = BuddyAlloc(14);
 * BuddyFree(alloc0);
 * void *alloc2 = BuddyAlloc(8);
 * BuddyFree(alloc2);
 * BuddyFree(alloc1);
 *
 * To feed a test file named "alloc_test1.test" into the experiment runner,
 * supply its relative path as the first argument, and supply the mode
 * ("firstfit" or "buddy") as the second argument. The runner will interpret the
 * operations in the file and execute them. It is up to you to design and
 * implement the experimental measurements.
 *
 */

struct addr_log {
  void **array;
  size_t count;
  size_t capacity;
};

struct addr_log InitAddrLog() {
  struct addr_log out = { NULL, 0, 0 };
  return out;
}

void AppendAddress(struct addr_log *log, void *addr) {
  if (log->count >= log->capacity) {
    log->array = realloc(log->array, log->capacity << 1);
    log->capacity <<= 1;
  }
  log->array[log->count++] = addr;
}


int main(int argc, char *argv[]) {
  if (argc != 3 ||
      (strcmp(argv[2], "firstfit") != 0 && strcmp(argv[2], "buddy") != 0)) {
    fprintf(stderr, "Usage: %s <test filename> firstfit/buddy", argv[0]);
    return 1;
  }
  FILE *testfile = fopen(argv[1], "r");
  if (testfile == NULL) {
    perror(argv[0]);
    return 1;
  }

  char tok[64];
  int param;

  enum { ALLOC, FREE, NONE } state = NONE;
  enum { FIRSTFIT, BUDDY } mode = strcmp(argv[2], "firstfit") == 0 ?
      FIRSTFIT : BUDDY;

  struct addr_log log = InitAddrLog();

  while (1) {
    if (state == NONE) {
      if (fscanf(testfile, "%s", tok) == EOF) {
        break;
      }
      if (strcmp(tok, "ALLOC") == 0) {
        state = ALLOC;
      } else if (strcmp(tok, "FREE") == 0) {
        state = FREE;
      } else {
        fprintf(stderr, "Unknown token: %s\n", tok);
        fclose(testfile);
        return 1;
      }
    } else {
      if (fscanf(testfile, "%d", &param) == EOF) {
        fprintf(stderr, "Test file ended unexpectedly! Check the last operation.\n");
        fclose(testfile);
        return 1;
      }
      if (state == ALLOC) {
        if (mode == FIRSTFIT) {
          AppendAddress(&log, FirstFitAlloc(param));
        } else {
          AppendAddress(&log, BuddyAlloc(param));
        }
      } else {
        if (mode == FIRSTFIT) {
          FirstFitFree(log.array[param]);
        } else {
          BuddyFree(log.array[param]);
        }
      }
      state = NONE;
    }
  }

  fclose(testfile);

  // TODO Measure system state as it pertains to the 50% rule and the Unused
  // Memory Rule. Display the measurements and discuss the results.
  
  return 0;
}
