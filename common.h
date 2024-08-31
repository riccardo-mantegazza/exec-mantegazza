#ifndef PSEUDO_EXEC_H
#define PSEUDO_EXEC_H

#include <setjmp.h>

extern jmp_buf env;

int pseudo_exec (const char* so_file, const char* func_name);
void to_be_interrupted();
void f1();
void f2();
void f3();
void f4();
void f5();
int tester (const char *func_name);

#endif