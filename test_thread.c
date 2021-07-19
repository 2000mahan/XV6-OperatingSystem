#include "types.h"
#include "stat.h"
#include "user.h"

void
run(void* arg)
{
  int id = *(int*) arg;
  id++;
  int i;
  sleep(100);
  for( i = 0 ; i < 4 ; i++){
    printf(1, "This is thread %d printing %d\n", id, i);
    if( id != 2 || i != 3)
      sleep(100);
    if (id == 1 && i == 1)
      sleep(100);
  }
  printf(1, "Thread %d finished execution\n", id);
  exit();
}


void
testThread(int n)
{
  int tid, i;
  for (i = 0; i < n; i++) {
    tid = thread_create(run, &i);
    sleep(10);
    if (tid < 0) {
      printf(1, "create thread failed\n");
    } else {
      printf(1, "create thread %d\n",i+1);
      sleep(10);
    }
  }
  
  // join
  for (i = 0; i < 5 ; i++) {
    tid = join();
  }
  printf(1, "all threads joined\n");
}

int
main(int argc, char *argv[]){
   testThread(3);
   exit();
}