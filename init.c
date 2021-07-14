// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PAGESIZE  4096

char *argv[] = { "sh", 0 };

int
main(void)
{
  int pid, jpid;
  // allocating 2 * pageSize for fptr in heap
  void *fptr = malloc(2 * (PAGESIZE));
  void *stack;

  if(fptr == 0)
  return -1;

  int mod = (uint)fptr % PAGESIZE;

  // the following if-else is for assigning page-aligned space to stack
  if(mod == 0)
    stack = fptr;
  else
    stack = fptr + (PAGESIZE - mod);

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    printf(1, "init: starting sh\n");

    pid = clone((void*)stack);
    
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((jpid=join()) >= 0 && jpid != pid)
      printf(1, "zombie!\n");
  }
}
