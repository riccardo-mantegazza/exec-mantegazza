#include <stdio.h>

#include "common.h"

int tester (const char *func_name) {
    int ret;
    ret = pseudo_exec ("./mylib.so", func_name);
    if (ret == -1) {
        printf ("An error occurred. Execution failed :(\n\n");
        return -1;
    }
    else {
        printf ("Execution successful! :)\n\n");
        return 0;
    }
}