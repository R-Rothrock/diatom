#!/usr/bin/make
# compiles stuff into object files

all: lib
	gcc dicp.c -shared -o lib/diatom-dicp.so
	gcc dscp.c -shared -o lib/diatom-dscp.so
lib:
	mkdir lib

clean:
	rm -rf lib
