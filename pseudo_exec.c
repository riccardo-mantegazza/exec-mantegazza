#include <stdio.h>
#include <dlfcn.h>

//The function returns 0 in case of success, -1 in case of failure
int pseudo_exec (const char* so_file, const char* func_name) {

    //Variables
    void* handle;
    void (*func)();

    //The .so file is loaded
    handle = dlopen (so_file, RTDL_LAZY);
    if (handle == NULL) {
        fprintf (stderr, "dlopen error: %s\n", dlerror());
        return -1; //REMEMBER TO PRINT A GLOBAL ERROR MESSAGE IN MAIN FUNCTION
    }

    //The symbol of the function is extracted
    func = (void (*)()) dlsym (handle, func_name);
    if (func == NULL) {
        fprintf (stderr, "dlopen error: %s\n", dlerror());
        return -1;
    }

    //The execution of the function begins
    printf ("Execution of function %s...\n", func_name);
    func();

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