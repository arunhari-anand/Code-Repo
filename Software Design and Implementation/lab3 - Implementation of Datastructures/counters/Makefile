# Makefile for 'set' module
#
# Borrows from the makefile for the set module provided by Prof. Xia
#Arun Anand, 2017

PROG = counters_test
OBJS = counters_test.o counters.o ../common/memory.o
LIBS =

all: counters_test
# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counters_test.o: counters.h
counters.o: counters.h


.PHONY: clean


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
