// data.h
// persistent and runtime data storage

static char *DATA_PATH;

int data_init() {
  /* Locates conf file.
   * If you don't run this, whatever happens is your fault.
   */
}

char *get_central_ip() {
  /* Gets central node IP from config file
   */
}

/* RUNTIME DATA STORAGE */

// so, basically, what the emulated program thinks of as file
// descriptors to read from (and write (eventually) to) will just
// be files.

// TODO work our kinks in design; they're there, somewhere...

void *setfd(const char *data) {
  // TODO
}

void *getfd(const char *loc) {
  // TODO
}
