CC = g++
CFLAGS = -std=c++11 -c

all: main

main: main.o base.o book.o movie.o music.o
	$(CC) main.o base.o book.o movie.o music.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

base.o: base.cpp
	$(CC) $(CFLAGS) base.cpp

book.o: book.cpp
	$(CC) $(CFLAGS) book.cpp

movie.o: movie.cpp
	$(CC) $(CFLAGS) movie.cpp

music.o: music.cpp
	$(CC) $(CFLAGS) music.cpp	

clean:
	rm -rf *o main