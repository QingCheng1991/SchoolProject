CC = g++
CCOPTS = -g -Wall -lm -std=c++11

huffman: huffman.cc node.o
	$(CC) $(CCOPTS) huffman.cc node.h -o huffman
	
node.o: node.h
	$(CC) $(CCOPTS) -c huffman.cc



	
clean:
	rm *.o