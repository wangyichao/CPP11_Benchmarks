SRCS=time_measurement.cpp syst_count.c	perf_util.c
OBJECTS=$(patsubst %.c,%.o,$(SRCS))
CFLAGS=-fopenmp -std=c++11
OPT=-O2
LIBS=-lpfm
CC1=g++
CC2=gcc

time_measurement: $(OBJECTS)
	$(CC1) $(OPT) $(CFLAGS) -o bin/$(CC2)$(OPT) $(OBJECTS) $(LIBS)

perf_util.o: perf_util.c perf_util.h
	$(CC2) $(OPT) $(CFLAGS) -c perf_util.c

syst_count.o: syst_count.c syst_count.h perf_util.h
	$(CC2) $(OPT) $(CFLAGS) -c syst_count.c

time_measurement.o: time_measurement.cpp
	$(CC1) $(OPT) $(CFLAGS) -c time_measurement.cpp
	

clean:
	rm -f *.o bin/gcc* bin/icc* bin/clang*
