# PA 5: Memory management

This is an unofficial programming assignment for memory management in Joseph
Pasquale's CSE 120/220, Principles of Operating Systems, at UC San Diego.
It incorporates important memory management concepts from the second half of 
the course, including:

- Fragmentation, the 50% rule, and the unused memory rule
- The Buddy System
- Segmented paged memory
- The CLOCK algorithm for page replacement

## Fragmentation

You will implement a memory allocator with a first-fit policy and then run some
experiments to measure the number of holes and their total size. You are then to
vary the experimental parameters and measure the response.

Read the _Fragmentation_ section in [wemix.h](wemix.h), which lists kernel-mode
functions you should write in [wemix.c](wemix.c). To assist your understanding
of these functions, here's an example test that should pass:

```c
// We start with the heap completely free
char *chunk = FirstFitAlloc(13); // round up to 16, a multiple of 4
assert(FirstFitBytesAllocated() == 16);
assert(FirstFitHoleCount() == 1);
// The hole extends from the end of the allocated chunk to the end of the 
// "physical memory"
char *chunk2 = FirstFitAlloc(8);
char *chunk3 = FirstFitAlloc(24);
assert(FirstFitHoleCount() == 1);
FirstFitFree(chunk2);
assert(FirstFitHoleCount() == 2);
char *chunk4 = FirstFitAlloc(4);
assert(chunk4 == chunk2); // chunk4 should be allocated where chunk2 used to be
assert(FirstFitHoleCount() == 2);
```

**Please implement `FirstFitAlloc`, `FirstFitFree`, `FirstFitBytesAllocated`,
and `FirstFitHoleCount` in `wemix.c`.**

## The Buddy System

Along with first fit, you will also implement a memory allocator utilizing the
Buddy System, which organizes physical memory into a binary tree. You will then
run some experiments to measure internal and external fragmentation.

In the _Buddy System_ section in [wemix.h](wemix.h), we have listed the
functions you will implement using the Buddy System. They should have an
identical interface to the corresponding functions under First Fit.

You may assume that each test will only interact with either First Fit or The
Buddy System.

**Please implement `BuddyAlloc`, `BuddyFree`, `BuddyBytesAllocated`, and
`BuddyHoleCount` in `wemix.c`.**

### Experimentation

Take a look at [`AllocExperiment.c`](AllocExperiment.c). It runs a memory
allocation and deallocation "program" according to a plain text input file. Your
goal with this file is to do the following:

1. Synthesize plain-text memory allocation and deallocation tests in the format
   accepted by `AllocExperiment.c` that roughly honor the assumptions of the 50%
   Rule and the Unused Memory Rule.
2. Complete `AllocExperiment.c`. Specifically, determine the metrics necessary
   to validate the rules and make the test runner print these metrics when
   finished.
3. Conduct one experiment with first fit and one experiment with the Buddy
   System. Comment on the resultant metrics. Do they align with the Rules? If
   not, why?

Please write your comments in the `AllocExperimentOutcome.txt` file.

## Segmented-paged Memory

You will write a simulation for the hardware functionality that performs
logical-to-physical address translation using the segmented-paged scheme from 
lecture. You will then combine this simulation with your memory allocator to
support a hypothetical system with multiple processes.

> UNDER CONSTRUCTION

## The CLOCK algorithm

Finally, you will upgrade your logical memory implementation into a virtual one
by implementing the CLOCK algorithm. In this PA's memory model, we represent
physical memory using a large array with static lifetime, while we represent the
disk using a memory-mapped file. You will write the procedures that load pages
from "disk" and write them to "disk".

> UNDER CONSTRUCTION

