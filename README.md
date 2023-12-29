# Diatom

**Diatom** ~~is~~ _will be_ a program capable of running the program of
one "central" computer on another "client" computer when imitating the
central computer's environment. This is accomplished with unencrypted
UDP communication and ptrace-based syscall emulation.

## Checklist

All of this will go in a changelog someday, but not now.

### 0.0.1

 - Design the protocols
   - [x] figure out which port I'm going to use
   - [x] decide whether the protocols are made on TCP or UDP (speed v
      reliability)
   - [x] make DSCP
     - `protocols/dscp.c`
     - `protocols/dscp.h`
   - [x] make DICP
     - `protocols/dicp.c`
     - `protocols/dicp.h`
   - [x] make a method for unpacking the protocols
     - `protocols/unpack.c`
     - `protocols/unpack.h`
   - [x] much makefile
     - `protocols/makefile`
   - [ ] tally all the things that a process can request from its
      kernel and make it possible.
 - Design the logging system
   - [x] make logging functions
     - `logging/logging.c`
     - `logging/logging.h`
   - [x] add conventional time format to the logs
     - `logging/logging.c`
   - [x] add makefile
     - `logging/makefile`
 - Diatom client
   - [x] sandbox environment
     - `diatom-client/env.c`
   - [ ] handle UDP
     - `diatom-client/handler.c`
   - [ ] manage threads
     - `diatom-client/threads.c`
   - [ ] get some persistent data storage
     - `diatom-client/data.c`
   - [ ] duck-tape it all together
     - `diatom-client/main.c`
   - [ ] write a makefile in which it works
     - `diatom-client/makefile`
   - [ ] write a service file for installation
     - `diatom-client/diatom-client.service`
   - [ ] add `make install` to makefile
     - `diatom-client/makefile`
 - Diatom central
   - [ ] make a friendly cli
     - `diatom-central/cli.c`
   - [ ] handle processes over UDP
     - `diatom-central/handler.c`
   - [ ] add persistent data storage
     - `diatom-central/data.c`
   - [ ] Elmer's glue it all together
     - `diatom-central/main.c`
   - [ ] write a makefile
     - `diatom-central/makefile`
   - [ ] add `make install` formula to makefile
     - `diatom-central/makefile`
 - Other
   - [x] add a build workflow
   - [ ] test it with Virtualbox and Ubuntu base images
   - [ ] add a test workflow?

### 0.0.2

 - handle forks and threads
 - configure AES options

### 0.0.3

 - handle `ptrace` calls.
 - handle `process_vm_readv` and `process_vm_writev` calls
 - Maybe add a status GUI to `diatom-central`

### 1.0.0

 - fix the many, many, problems that will come along the way.
 - thoroughly test this thing for vulnerabilities

## Installation

Can't say.

## Usage

Can't say.

## Contribution

Can't say.

## Why I called this Diatom

A [diatom](https://diatoms.org/what-are-diatoms) is a unicellular
kind of algae and is the base form of plankton. I found this close
enough (but not too close) to amoeba, as in the old [amoeba
distributed operating system
](https://cs.vu.nl/pub/amoeba/amoeba.html) from the 90s.
