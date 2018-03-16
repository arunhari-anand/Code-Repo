# Makefile for 'set' module
#
# Borrows from the makefile for the set module provided by Prof. Xia
#Arun Anand, 2017

PROG = set_test
OBJS = set_test.o set.o ../common/memory.o
LIBS =

all: set_test
# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

set_test.o: set.h
set.o: set.h
readline.o: ../common/readlinep.h

.PHONY: clean


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
