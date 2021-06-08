all: executavel

executavel: main.o RB.o
	gcc -o executavel main.o RB.o

RB.o: RB.c RB.h
	gcc -c RB.c -Wall

main.o: main.c
	gcc -c main.c -Wall

clean:
	rm main.o RB.o executavel