all: executavel

executavel: main.o huffman.o
	gcc -o executavel main.o huffman.o

huffman.o: huffman.c huffman.h
	gcc -c huffman.c -Wall

main.o: main.c huffman.h
	gcc -c main.c -Wall

clean:
	rm executavel.exe main.o huffman.o