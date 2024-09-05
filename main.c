#include <stdio.h>

#include "disastrOS.h"
#include "disastrOS_globals.h"
#include "disastrOS_syscalls.h"

int main (int argc, char** argv) {
    if (argc < 3) {
        fprintf (stderr, "Usage: %s mylib.so my_function\n", argv[0]);
        return 1;
    }

    const char* so_file = argv[1];
    const char* func_name = argv[2];

    if (running == NULL) {
        fprintf (stderr, "Error: no running process context available.\n");
        return 1;
    }

    running -> syscall_args[0] = (long)so_file;
    running -> syscall_args[1] = (long)func_name;

    internal_spawn();

    if (running -> syscall_retvalue < 0) {
        printf ("An error occurred in the pseudo_exec\n");
    }

    int ret = pseudo_exec (so_file, func_name);
    if (ret == -1) fprintf (stderr, "An error occurred\n");
    printf ("The main process finished: the pseudo_exec didn't work\n");
    return 0;
}