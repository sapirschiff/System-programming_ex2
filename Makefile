CFLAGS = -Wall -g
CC = gcc
AR = ar

all: connections

my_mat.o: my_mat.c my_mat.h
	$(CC) $(CFLAGS) -fPIC -c my_mat.c -o my_mat.o

main.o: main.c my_mat.h
	$(CC) $(CFLAGS) -fPIC -c main.c -o main.o

libmy_mat.a: my_mat.o 
	$(AR) -rcs libmy_mat.a my_mat.o 

connections: main.o libmy_mat.a
	$(CC) -o connections main.o libmy_mat.a $(CFLAGS)

.PHONY: clean all

clean: 
	rm -f *.o *.a  connections