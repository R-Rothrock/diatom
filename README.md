# Diatom

**Diatom** ~~is~~ _will be_ a interface by which a "central node" can
connect to and utilize the CPUs of other "nodes" on the network,
resulting in a linear distrubuted computation network, in which the
central node controls all other nodes. All nodes communicate with
each other via the **Diatom Superior Communication Protocol** used by
the central node and the **Diatom Inferior Communication Protocol**
used by lesser nodes for requesting assets such as files and network
sockets. Both will use UDP for communication on port 12036, removing
the need for connections.

I envision this being a sizable project, and so I would very much
appreciate anyone's contributions. You can take a look at the checklist
below and feel free to email me with any questions.

## TODO

A lot

 - Design the protocols
   - [x] figure out which port I'm going to use
   - [x] decide whether the protocols are made on TCP or UDP (speed v reliability)
   - [x] make DSCP
     - `protocols/dscp.c`
     - `protocols/dscp.h`
   - [x] make DICP
     - `protocols/dicp.c`
     - `protocols/dicp.h`
   - [X] make a method for unpacking the protocols
     - `protocols/unpack.c`
     - `protocols/unpack.h`
   - [x] much makefile
     - `protocols/makefile`
 - Diatom client
   - [ ] sandboxing
     - `diatom_client/env.c`
   - [ ] do some other stuff
     - `diatom_client/handler.c`
     - `diatom_client/threads.c`
   - [ ] duck-tape it all together
     - `diatom_client/main.c`
   - [ ] write a makefile in which it works
     - `diatom_client/makefile`
 - Diatom central
   - [ ] make a friendly cli
   - [ ] dp some other stuff
   - [ ] Elmer's glue to cli to the rest
   - [ ] more makefile
 - Other
   - [x] nothing could be more fun than CI
   - [ ] use a bunch of vms running Ubuntu base images to test it
   - [ ] find it doesn't work, delete repo, throw things

## To not do (yet, anyways)
 - Handle forks and threads
 - Make `ptrace` work at the same time

One day, but not today...

### Why I called this Diatom

A [diatom](https://diatoms.org/what-are-diatoms) is a unicellular
kind of algae and is the base form of plankton. I found this close
enough (but not too close) to amoeba, as in the old [amoeba
distributed operating system
](https://cs.vu.nl/pub/amoeba/amoeba.html) from the 90s.
