#include <stdio.h>
#include <unistd.h>
#include <poll.h>

#include "disastrOS.h"

// we need this to handle the sleep state
void sleeperFunction(void* args){
  printf("Hello, I am the sleeper, and I sleep %d\n",disastrOS_getpid());
  while(1) {
    getc(stdin);
    disastrOS_printStatus();
  }
}

void childFunction(void* args){
  printf("Hello, I am the child function %d\n",disastrOS_getpid());
  printf("I will iterate a bit, before terminating\n");
  for (int i=0; i<(disastrOS_getpid()+1); ++i){
    printf("PID: %d, iterate %d\n", disastrOS_getpid(), i);
    disastrOS_sleep((20-disastrOS_getpid())*5);
  }
  printf("PID: %d, terminating\n", disastrOS_getpid());
  disastrOS_exit(disastrOS_getpid()+1);
}


void initFunction(void* args) {
  disastrOS_printStatus();
  printf("hello, I am init and I just started\n");
  disastrOS_spawn(sleeperFunction, 0);
  char** argv = (char**) args;
  
  if (argv[1] && argv[2]) {
    printf("Calling pseudo_exec with shared library: %s and function: %s\n", argv[1], argv[2]);
    int ret = pseudo_exec(argv[1], argv[2]);
    if (ret == -1) printf ("something went wrong in the pseudo_exec\n");
  } else {
    printf("Error: Please provide both a shared library and a function name.\n");
  }


  printf("I feel like to spawn 10 nice threads\n");
  int alive_children=0;
  for (int i=0; i<10; ++i) {
    disastrOS_spawn(childFunction, 0);
    alive_children++;
  }

  disastrOS_printStatus();
  int retval;
  int pid;
  while(alive_children>0 && (pid=disastrOS_wait(0, &retval))>=0){ 
    disastrOS_printStatus();
    printf("initFunction, child: %d terminated, retval:%d, alive: %d \n",
	   pid, retval, alive_children);
    --alive_children;
  }
  printf("shutdown!");
  disastrOS_shutdown();
}

int main(int argc, char** argv){
  /*// we create the init process processes
  // the first is in the running variable
  // the others are in the ready queue
  printf("the function pointer is: %p", childFunction);
  // spawn an init process
  printf("start\n");
  disastrOS_start(initFunction, 0, "logfile.txt");
  printf ("main process ended\n");
  return 0;*/
  if (argc < 3) {
    printf("Usage: %s <shared_library.so> <function_name>\n", argv[0]);
    return -1;
  }

  printf("the function pointer is: %p\n", childFunction);
  printf("start\n");
  disastrOS_start(initFunction, argv, "logfile.txt");
  printf ("main process ended\n");
  return 0;
}
