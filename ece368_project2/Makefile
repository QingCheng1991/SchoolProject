CC = g++
CCOPTS = -g -Wall -lm -std=c++11

all: polyexam polytest clean

polyexam: polyexam.cc poly.o
	$(CC) $(CCOPTS) polyexam.cc poly.o -o polyexam

polytest: polytest.cc poly.o
	$(CC) $(CCOPTS) polytest.cc poly.o -o polytest

poly.o: poly.cc poly.h
	$(CC) $(CCOPTS) -c poly.cc

clean:
	rm -f *.o core
