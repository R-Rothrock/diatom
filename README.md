# Diatom

**Diatom** ~~is~~ _will be_ a interface by which a "central node" can
connect to and utilize the CPUs of other "nodes" on the network,
resulting in a linear distrubuted computation network, in which the
central node controls all other nodes. All nodes communicate with
each other via the **Diatom Superior Communication Protocol** used by
the central node and the **Diatom Inferior Communication Protocol**
used by lesser nodes for requesting assets such as files and network
sockets. Both will use UDP for communication on port 5352, removing
the need for connections.

## TODO

Literally f***ing everything

 - Design the protocols
   - [x] figure out which port I'm going to use
   - [x] decide whether the protocols are made on TCP or UDP (speed v
   reliability)
   - [ ] cryptography (AES-256 with predefined keys)
   - [ ] make the damn protocols
   - [ ] make a method for interpreting the protocols
 - Diatom client
   - [ ] do some friendly neighborhood syscall hooking
   - [ ] not to mention `process_vm_ready`
   - [ ] duck-tape it all together
   - [ ] write a makefile in which it works
 - Diatom central
   - [ ] make a friendly cli
   - [ ] Elmer's glue to cli to the rest
   - [ ] more makefile
 - Finishing up
   - [x] nothing could be more fun than CI
   - [ ] use a bunch of vms running Ubuntu base images to test it
   - [ ] find it doesn't f***ing work, throw computer

## To not do (yet, anyways)
 - Handle forks and threads
 - Make `ptrace` work at the same time
 - execute anything as admin

## Wanna contribute?

Feel free. Put in an issue and I'll specify what needs to be done.

Fair warning: you probably don't, though.

### Why I called this Diatom

A [diatom](https://diatoms.org/what-are-diatoms) is a unicellular
kind of algae and is the base form of plankton. I found this close
enough (but not too close) to amoeba, as in the old [amoeba
distributed operating system
](https://cs.vu.nl/pub/amoeba/amoeba.html) from the 90s.
