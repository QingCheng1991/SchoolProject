
CC = g++
CCOPTS = -g -Wall -lm -std=c++11

carwash: carwash.cc washevent.o customer.o
	$(CC) $(CCOPTS) carwash.cc customer.h washevent.h -o carwash
	
customer.o: customer.h
	$(CC) $(CCOPTS) -c carwash.cc

washevent.o: washevent.h
	$(CC) $(CCOPTS) -c carwash.cc

	
clean:
	rm *.o