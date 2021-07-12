#include "types.h"
#include "stat.h"
#include "user.h"

#define PAGESIZE  4096

int
thread_create(void (*fn) (void *), void *arg)
{

// allocating 2 * pageSize for fptr in heap
void *fptr = malloc(2 * (PAGESIZE));
void *stack;
// current process
struct proc *curproc;
// new process
struct proc *np;

if(fptr == 0)
return -1;

int mod = (uint)fptr % PAGESIZE;

// the following if-else is for assigning page-aligned space to stack
if(mod == 0)
  stack = fptr;
else
  stack = fptr + (PAGESIZE - mod);

int thread_id = clone((void*)stack);

// clone failed
if(thread_id < 0)
    printf(1, "clone failed");
    
// child
else if(thread_id = 0){
    // call the function passed to thread_create
    (fn)(arg);
    // free space when function is finished
    free(stack);
    exit();
}
    return thread_id;

}