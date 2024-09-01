#ifndef PSEUDO_EXEC_H
#define PSEUDO_EXEC_H

#include <setjmp.h>

extern jmp_buf env;

// Dichiarazioni delle funzioni
int pseudo_exec(const char* so_file, const char* func_name);
void to_be_interrupted();

#endif // PSEUDO_EXEC_H
