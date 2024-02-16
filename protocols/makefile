#!/usr/bin/make
# compiles stuff into object files

all: dicp.o dscp.o unpack.o bin
	mv dicp.o dscp.o unpack.o bin

dicp.o:
	gcc -c dicp.c -o dicp.o | wc -l

dscp.o:
	gcc -c dscp.c -o dscp.o

unpack.o:
	gcc -c unpack.c -o unpack.o

bin:
	mkdir bin

clean:
	rm -rf bin
