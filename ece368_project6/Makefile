CC = g++
CCOPTS = -g -Wall -lm -std=c++11


sorttest: sorttest.cc sort.o 
	$(CC) $(CCOPTS) sorttest.cc sort.o -o sorttest

	
sort.o: sort.cc sort.h
	$(CC) $(CCOPTS) -c sort.cc



clean:
	rm -f *.o core