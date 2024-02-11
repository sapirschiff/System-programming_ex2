CFLAGS = -Wall -g
CC = gcc
AR = ar

.PHONY: clean all

all: my_graph my_Knapsack

my_mat.o: my_mat.c my_mat.h
	$(CC) $(CFLAGS) -fPIC -c my_mat.c -o my_mat.o

my_graph.o: my_graph.c my_mat.h
	$(CC) $(CFLAGS) -fPIC -c my_graph.c -o my_graph.o

my_Knapsack.o: my_Knapsack.c
	$(CC) $(CFLAGS) -c my_Knapsack.c

libmy_mat.a: my_mat.o 
	$(AR) -rcs libmy_mat.a my_mat.o 

my_graph: my_graph.o libmy_mat.a
	$(CC) -o my_graph my_graph.o libmy_mat.a $(CFLAGS)

my_Knapsack: my_Knapsack.o 
 	$(CC) $(CFLAGS) my_Knapsack.o -o my_Knapsack
	
clean: 
	rm -f *.o *.a  my_graph 