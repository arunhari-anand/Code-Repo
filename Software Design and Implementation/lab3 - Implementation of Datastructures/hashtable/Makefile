# Makefile for 'set' module
#
# Borrows from the makefile for the set module provided by Prof. Xia
#Arun Anand, 2017

PROG = hashtable_test
OBJS = hashtable_test.o hashtable.o ../common/memory.o ../set/set.o jhash.o
LIBS =

all: hashtable_test
# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common -I../set
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtable_test.o: hashtable.h
hashtable.o: hashtable.h jhash.h ../set/set.h ../common/memory.h
readline.o: ../common/readlinep.h

.PHONY: clean


clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
