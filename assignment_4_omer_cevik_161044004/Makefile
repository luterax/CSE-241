CC = g++
CFLAGS = -std=c++11 -c

all: main

main: main.o gates.o input.o output.o not.o or.o and.o ff.o decoder.o
	$(CC) main.o gates.o input.o output.o not.o or.o and.o ff.o decoder.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

gates.o: gates.cpp gates.h
	$(CC) $(CFLAGS) gates.cpp

input.o: input.cpp gates.h input.h
	$(CC) $(CFLAGS) input.cpp

output.o: output.cpp gates.h output.h
	$(CC) $(CFLAGS) output.cpp

not.o: not.cpp gates.h not.h
	$(CC) $(CFLAGS) not.cpp

or.o: or.cpp gates.h or.h
	$(CC) $(CFLAGS) or.cpp

and.o: and.cpp gates.h and.h
	$(CC) $(CFLAGS) and.cpp

ff.o: ff.cpp gates.h ff.h
	$(CC) $(CFLAGS) ff.cpp

decoder.o: decoder.cpp gates.h decoder.h
	$(CC) $(CFLAGS) decoder.cpp

clean:
	rm -rf *o main