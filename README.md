# Diatom

**Diatom** ~~is~~ _will be_ a interface by which a "central node" can
connect to and utilize the CPUs of other "nodes" on the network,
resulting in a distributed computation network, in which the
central node controls all other nodes.

I envision this being a sizable project, and so I would very much
appreciate anyone's contributions. You can take a look at the checklist
below and feel free to email me with any questions.

## My jumbled notes to myself

All nodes communicate with each other via the **Diatom Superior Communication
Protocol** used by the central node and the **Diatom Inferior Communication
Protocol** used by lesser nodes for requesting assets such as files and network
sockets. Both will use UDP for communication on port 12036, removing the need
for connections.

For Diatom Central, there will simply be an executable with some SQLite
databases. As for Diatom Client, there will be a service running.

To keep track of the different nodes on the network, there will need to be a
database for keeping track, and, to edit this file, one will need superuser
privileges. Keep in mind to **only add computers you trust into the config
file.** Any computer you add will be capable of accessing files, network
sockets, and possible more. At first, this database will be edited manually by a
`sudo` instance. Then, I'll likely add another executable to add some QoL to the
picture.

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

## Why I called this Diatom

A [diatom](https://diatoms.org/what-are-diatoms) is a unicellular
kind of algae and is the base form of plankton. I found this close
enough (but not too close) to amoeba, as in the old [amoeba
distributed operating system
](https://cs.vu.nl/pub/amoeba/amoeba.html) from the 90s.
