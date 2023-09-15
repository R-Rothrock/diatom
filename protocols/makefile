#!/usr/bin/make
# compiles stuff into object files

all: lib
	gcc dicp.c dscp.c unpack.c -shared -o lib/diatom-protocols.so
lib:
	mkdir lib

clean:
	rm -rf lib
