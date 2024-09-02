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
  int ret = pseudo_exec (so_file, func_name);
  if (ret == -1) printf ("An error occured\n");

  printf("Launcher terminating\n");
  return 0;
}
