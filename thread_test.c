#include "types.h"
#include "stat.h"
#include "user.h"

void
sleep_func(void* arg)
{
  printf(1, "welcome to sleep_func\n");
  int time = *(int*)arg;
  sleep(time);
  exit();
}

// some clone calls will fail due to xv6 supporting only 64 processes.
void
create_n_threads(int n)
{
  printf(1, "welcome to test_n_threads\n");
  int tid, i, pid;
  int threadCounter = 0;
  int time = 100;
  for (i = 0; i < n; i++) {
    tid = thread_create(sleep_func, &time);
    sleep(10);
    if (tid < 0) {
      printf(1, "create thread failed\n");
    } else {
      printf(1, "create thread (id = %d)\n", tid);
      threadCounter++;
    }
  }

  pid = fork();
  if (pid < 0) {
    printf(1, "create process failed\n");
  } else if (pid == 0) {
    printf(1, "fork: child\n");
    exit();
  } else {
    printf(1, "create process (id = %d)\n", pid);
    if (wait() != pid) {
      printf(2, "create_n_threads: wait unexpected process (expected = %d)\n", pid);
    }
  }
  
  // join
  for (i = 0; i < threadCounter; i++) {
    tid = join();
    printf(1, "tid = %d join \n", tid);
  }
}

int
main(int argc, char *argv[])
{
   create_n_threads(100);
   exit();
}