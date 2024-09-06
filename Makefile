CC=gcc
CCOPTS=--std=gnu99 -Wall  -Ofast -D_DISASTROS_DEBUG_
AR=ar
HEADERS=disastrOS.h\
	disastrOS_constants.h\
	disastrOS_globals.h\
	disastrOS_pcb.h\
	disastrOS_syscalls.h\
	disastrOS_timer.h\
	linked_list.h\
	pool_allocator.h

OBJS=pool_allocator.o\
     linked_list.o\
     disastrOS_timer.o\
     disastrOS_pcb.o\
     disastrOS.o\
     disastrOS_wait.o\
     disastrOS_fork.o\
     disastrOS_spawn.o\
     disastrOS_exit.o\
     disastrOS_sleep.o\
     disastrOS_shutdown.o\
     disastrOS_schedule.o\
     disastrOS_preempt.o\
	 pseudo_exec.o

MYLIB_OBJS=my_functions.o
MYLIB = mylib.so
BINS=disastrOS_test

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

$(MYLIB): $(MYLIB_OBJS)
	$(CC) -fPIC -shared -o $@ $^

$(BINS): $(OBJS) $(MYLIB)
	$(CC) $(CCOPTS) -o $@ $^ -Wl,-rpath=. -lmylib

disastrOS_test:		disastrOS_test.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)