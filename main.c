#include <stdio.h>

#include "project.c"

int main () {
    int ret;
    ret = pseudo_exec ("./mylib.so", "my_function");
    if (ret == -1) {
        printf ("An error occurred. Execution failed :(");
    }
    else {
        printf ("Execution successful! :)");
    }
    return 0;
}