#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "disastrOS.h"

// The function returns -1 in case of an error
int pseudo_exec(const char* so_file, const char* func_name) {
    void* handle;
    void (*func)();

    // Loading of the .so file
    handle = dlopen(so_file, RTLD_LAZY);
    if (handle == NULL) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return -1;
    }

    // Extraction of the symbol of the function
    func = (void (*)()) dlsym(handle, func_name);
    if (func == NULL) {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        dlclose(handle);
        return -1;
    }

    // Execution of the function
    printf("Execution of function %s...\n", func_name);
    func();

    // Closing the shared object
    if (dlclose(handle) != 0) {
        fprintf(stderr, "dlclose error: %s\n", dlerror());
        return -1;
    }

    // End the main process
    exit (0);
}