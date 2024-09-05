# Compiler settings
CC=gcc
CCOPTS=--std=gnu99 -Wall -Ofast  
AR=ar

# Headers
HEADERS=disastrOS.h\
	disastrOS_constants.h\
	disastrOS_globals.h\
	disastrOS_pcb.h\
	disastrOS_syscalls.h\
	linked_list.h\
	pool_allocator.h\

# Object files for the static library
OBJS=pool_allocator.o\
     linked_list.o\
     disastrOS_pcb.o\
     disastrOS.o\
     disastrOS_wait.o\
     disastrOS_fork.o\
     disastrOS_spawn.o\
     disastrOS_exit.o\
     disastrOS_shutdown.o\
     disastrOS_schedule.o\
     disastrOS_preempt.o\
     pseudo_exec.o  # Added pseudo_exec.o

# Static library
LIBS=libdisastrOS.a

# Shared library for my_function
SOFILE=mylib.so

# Executable binaries
BINS=disastrOS_test launcher

# Phony targets
.phony: clean all

# Default target: build everything
all: $(LIBS) $(SOFILE) $(BINS)

# Rule for creating object files
%.o: %.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@ $<

# Rule for creating the static library
libdisastrOS.a: $(OBJS)
	$(AR) -rcs $@ $^

# Rule for creating the shared library (.so)
$(SOFILE): my_functions.o
	$(CC) -shared -o $@ $^

# Rule for creating the launcher executable
launcher: main.o pseudo_exec.o $(LIBS) $(SOFILE)
	$(CC) $(CCOPTS) -o $@ main.o pseudo_exec.o -L. -ldisastrOS -ldl

# Rule for creating the disastrOS_test executable
disastrOS_test: disastrOS_test.o $(LIBS)
	$(CC) $(CCOPTS) -o $@ disastrOS_test.o -L. -ldisastrOS -ldl

# Rule for creating object files for main and pseudo_exec
main.o: main.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@ $<

pseudo_exec.o: pseudo_exec.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@ $<

# Clean rule to remove object files, libraries, and binaries
clean:
	rm -rf *.o *~ $(LIBS) $(SOFILE) $(BINS)

