CFLAGS= -Wall -fpic -coverage -lm -std=c99

player: testme.c
	gcc -o testme testme.c -g $(CFLAGS)
	./testme

all: testme

clean:
	rm -f *.o testme.exe *.so *.out
