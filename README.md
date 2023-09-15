# Diatom

**Diatom** ~~is~~ _will be_ a interface by which a "central node" can
connect to and utilize the CPUs of other "nodes" on the network,
resulting in a distributed computation network, in which the
central node controls all other nodes. All nodes communicate with
each other via the **Diatom Superior Communication Protocol** used by
the central node and the **Diatom Inferior Communication Protocol**
used by lesser nodes for requesting assets such as files and network
sockets. Both will use UDP for communication on port 12036, removing
the need for connections.

I envision this being a sizable project, and so I would very much
appreciate anyone's contributions. You can take a look at the checklist
below and feel free to email me with any questions.

## Checklist

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
 - Diatom client
   - [ ] sandbox environment
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
   - [ ] GUI?
     - `diatom-central/gui.c` ???
   - [ ] Elmer's glue it all together
     - `diatom-central/main.c`
   - [ ] write a makefile
     - `diatom-central/makefile`
   - [ ] add a service files
     - `diatom-central/diatom-central.service`
   - [ ] add `make install` formula to makefile
     - `diatom-central/makefile`
 - Other
   - [x] add a build workflow
   - [ ] test it with Virtualbox and Ubuntu base images
   - [ ] add a test workflow?

### 1.0.0
 - handle forks and threads
 - handle `ptrace`, `process_vm_readv`, etc.
 - maybe make that GUI?
 - fix the many problems that will inevitably come across the path


## Why I called this Diatom

A [diatom](https://diatoms.org/what-are-diatoms) is a unicellular
kind of algae and is the base form of plankton. I found this close
enough (but not too close) to amoeba, as in the old [amoeba
distributed operating system
](https://cs.vu.nl/pub/amoeba/amoeba.html) from the 90s.
