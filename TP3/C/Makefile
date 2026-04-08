CC= gcc
# Mode silencieux : plus de -Wall ni de -pedantic, et ajout de -w
CFLAGS= -std=c99 -O3 -w

OBJ = binomial.o main_binomial.o

all: test_binomial

test_binomial: $(OBJ)
	$(CC) $(CFLAGS) -o test_binomial $(OBJ)

binomial.o: binomial.c binomial.h
	$(CC) $(CFLAGS) -c binomial.c

main_binomial.o: main_binomial.c binomial.h
	$(CC) $(CFLAGS) -c main_binomial.c

clean:
	rm -f *.o test_binomial *~