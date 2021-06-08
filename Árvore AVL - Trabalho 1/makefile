all: executavel

executavel: main.o AVL.o
	gcc -o executavel main.o AVL.o

AVL.o: AVL.c AVL.h
	gcc -c AVL.c -Wall

main.o: main.c
	gcc -c main.c -Wall

clean:
	rm executavel main.o AVL.o