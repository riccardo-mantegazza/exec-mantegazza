#include <stdio.h>

#include "pseudo_exec.c"
#include "test.c"

int main () {
    int correct = 0;
    int ret = 0;

    printf ("f1 test:\n\n");
    ret = tester("f1");
    if (ret == 0) correct++;

    printf ("f2 test:\n\n");
    ret = tester("f2");
    if (ret == 0) correct++;

    printf ("f3 test:\n\n");
    ret = tester("f3");
    if (ret == 0) correct++;

    printf ("f4 test:\n\n");
    ret = tester("f4");
    if (ret == 0) correct++;

    printf ("f5 test:\n\n");
    ret = tester("f5");
    if (ret == 0) correct++;

    printf ("%d/5 test passed.\n");
    return 0;
}