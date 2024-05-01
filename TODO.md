# TODO

All the things that separate this project from being actual software.

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
     - `protocols/info.h`
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
   - [ ] handle _every_, **single**, system call.
   - [x] handle UDP
     - `diatom-client/handler.c`
   - [x] get some persistent data storage
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
   - [x] learn Radare2.
 - thoroughly test this thing for vulnerabilities
