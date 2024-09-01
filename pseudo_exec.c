#include <stdio.h>
#include <dlfcn.h>
#include <setjmp.h>

#include "common.h"


jmp_buf env;

//The function returns 0 in case of success, -1 in case of failure
int pseudo_exec (const char* so_file, const char* func_name) {

    //Variables
    void* handle;
    void (*func)();

    //The .so file is loaded
    handle = dlopen (so_file, RTLD_LAZY);
    if (handle == NULL) {
        fprintf (stderr, "dlopen error: %s\n", dlerror());
        return -1;
    }

    //The symbol of the function is extracted
    func = (void (*)()) dlsym (handle, func_name);
    if (func == NULL) {
        fprintf (stderr, "dlopen error: %s\n", dlerror());
        dlclose (handle);
        return -1;
    }

    //The execution of the function begins
    printf ("Execution of function %s...\n", func_name);

    if (setjmp (env) == 0) {
        printf ("pseudo_exec: interrupting the execution\n");
        printf ("Hello! We are in the other context!\n");
        longjmp(env, 1);
    }
    else {
        printf ("pseudo_exec: resuming the execution\n");
        func();
    }

    //The shared object is closed
    int ret = 0;
    ret = dlclose (handle);
    if (ret == -1) {
        fprintf (stderr, "dlclose error: %s\n", dlerror());
        return -1;
    }

    //End of the exec
    return 0;
}