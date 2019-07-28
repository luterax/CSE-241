CC = g++
CFLAGS = -std=c++11 -c

all:main

main: main.o SparseVector.o SparseMatrix.o
	$(CC) main.o SparseVector.o SparseMatrix.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

SparseVector.o: SparseVector.cpp SparseVector.h
	$(CC) $(CFLAGS) SparseVector.cpp

SparseMatrix.o: SparseMatrix.cpp SparseMatrix.h
	$(CC) $(CFLAGS) SparseMatrix.cpp

clean:
	rm -rf *o main