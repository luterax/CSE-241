CC = g++
CFLAGS = -std=c++11 -c

all: main

main: main.o reader.o linkedlist.o
	$(CC) main.o reader.o linkedlist.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

reader.o: reader.cpp
	$(CC) $(CFLAGS) reader.cpp

linkedlist.o: linkedlist.cpp
	$(CC) $(CFLAGS) linkedlist.cpp

clean:
	rm -rf *o main