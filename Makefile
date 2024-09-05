CC=gcc
CCOPTS=--std=gnu99 -Wall 
AR=ar

# Headers
HEADERS=disastrOS.h\
	disastrOS_constants.h\
	disastrOS_globals.h\
	disastrOS_pcb.h\
	disastrOS_syscalls.h\
	linked_list.h\
	pool_allocator.h\

# Object files
OBJS=linked_list.o\
     disastrOS_pcb.o\
     disastrOS.o\
     disastrOS_spawn.o\
     pseudo_exec.o\
     main.o\
     pool_allocator.o\
     disastrOS_shutdown.o\
     disastrOS_fork.o\
     disastrOS_exit.o\
     disastrOS_wait.o\
     disastrOS_preempt.o\
     disastrOS_schedule.o


# Shared library objects
MYLIB_OBJS=my_functions.o

# Shared library
MYLIB=libmylib.so

# Executable
BINS=launcher

.phony: clean all

# Default target
all: $(MYLIB) $(BINS)

# Rule to compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

# Rule to build the shared library
$(MYLIB): $(MYLIB_OBJS)
	$(CC) -shared -o $@ $^

# Rule to build the executable
$(BINS): $(OBJS) $(MYLIB)
	$(CC) $(CCOPTS) -o $@ $^ -L. -lmylib

# Clean rule
clean:
	rm -rf *.o *~ $(MYLIB) $(BINS)
