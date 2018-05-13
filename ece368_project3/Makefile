CC = g++
CCOPTS = -g -Wall -lm -std=c++11


catalog: catalog.cc book.o booklist.o
	$(CC) $(CCOPTS) catalog.cc booklist.o book.o -o catalog

	
book.o: book.cc book.h
	$(CC) $(CCOPTS) -c book.cc

booklist.o: booklist.cc booklist.h
	$(CC) $(CCOPTS) -c booklist.cc

clean:
	rm -f *.o core