#include <stdio.h>

#include "common.h"

int main (int argc, char** argv) {
    if (argc < 3) {
        fprintf (stderr, "Usage: %s mylib.so my_function\n", argv[0]);
        return 1;
    }

    const char* so_file = argv[1];
    const char* func_name = argv[2];

    int ret = pseudo_exec (so_file, func_name);
    if (ret == -1) fprintf (stderr, "An error occurred\n");
    printf ("The main process finished: the pseudo_exec didn't work\n");
    return 0;
}