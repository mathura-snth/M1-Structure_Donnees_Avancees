CC= gcc
CXXFLAGS= -Wall -ansi --pedantic -O3

LIB = -lm


all: tas_binaire

tas_binaire: binaire.o analyzer_binaire.o main_binaire.o
	$(CC) $(CFLAGS) -o tas_binaire binaire.o analyzer_binaire.o main_binaire.o $(LIB)

binaire.o: binaire.c binaire.h
	$(CC) $(CFLAGS) -c binaire.c

analyzer_binaire.o: analyzer_binaire.c analyzer_binaire.h
	$(CC) $(CFLAGS) -c analyzer_binaire.c

main_binaire.o: main_binaire.c binaire.h analyzer_binaire.h
	$(CC) $(CFLAGS) -c main_binaire.c

clean:
	rm -f *.o tas_binaire