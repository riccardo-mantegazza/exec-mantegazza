#include <stdio.h>


void my_function() {
    for (int i = 0; i < 10; i++) {
        printf("Step %d in my_function...\n", i + 1);
    }
    printf("Hello from my_function in the shared object!\n");
}
 