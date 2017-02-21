INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS= -DRUN_TIMING_ANALYSIS_TEST -DRUN_PROCESSOR_UTIL_TEST -D$(EX_NUM)
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= feasibility_tests_llf.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:    feasibility_tests_llf

clean:
	-rm -f *.o *.d
	-rm -f feasibility_tests_llf

feasibility_tests_llf: feasibility_tests_llf.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lm

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
