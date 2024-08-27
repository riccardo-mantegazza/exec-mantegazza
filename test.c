#include <stdio.h>

#include "main.c"

int tester (const char *func_name) {
    int ret;
    ret = pseudo_exec ("./mylib.so", func_name);
    if (ret == -1) {
        printf ("An error occurred. Execution failed :(");
        return -1;
    }
    else {
        printf ("Execution successful! :)");
        return 0;
    }
}