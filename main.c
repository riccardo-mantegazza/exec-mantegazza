#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "common.h"

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("usage: %s <int> <path> <args>\n", argv[0]);
    printf(" <int> number of instances\n");
    printf(" <path> executable to launch\n");
    printf(" <args> arguments passed to each instance of the executable\n");
    return 1;
  }

  int num_instances = atoi(argv[1]);
  const char* so_file = argv[2];
  const char* func_name = argv[3];
  int active_instances = 0;

  for (int i = 0; i < num_instances; ++i) {
    pid_t child_pid = fork();
    if (child_pid < 0) {
      printf("Failed to fork, errno=%s\n", strerror(errno));
      return 1;
    } else if (child_pid == 0) {
      int result = pseudo_exec(so_file, func_name);
      exit (result);
    } else {
      active_instances++;
    }
  } 

  int status;
  while (active_instances) {
    pid_t child_pid = wait(&status);
    if (child_pid > 0) {
      printf("Process %d terminated, remaining instances: %d\n", child_pid, active_instances - 1);
      active_instances--;
    } else {
      printf("Failed to wait, errno=%s\n", strerror(errno));
      return 1;
    }
  }

  printf("Launcher terminating\n");
  return 0;
}
