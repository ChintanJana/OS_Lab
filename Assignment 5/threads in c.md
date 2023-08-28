## Basics
Processes
  - concurrency
  - isolation

Threads
- gives concurrency without isolation
  - part of same process
  - work on 2 different task while sharing progress
- have different call stacks but use the same memory space
  - one thread can write into the memory of naother thread
    - easier to communicate but can be prolematic

### pthread - POSIX Threads
- int pthread_create - creates an execution of thread

```
#include <pthreads.h>

```
        
