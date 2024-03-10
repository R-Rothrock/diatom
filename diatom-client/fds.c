// fd.c
// handling file descriptiors

// okay, so this is going to have to have a sort of database system
// preferably in memory. How? No idea!


enum fd_type {
  FD_TYPE_FILE,
  // TODO
} __attribute__((PACKED));

struct fd {
  enum fd_type type;
  char *loc;
  char *realloc;
}

struct fd` *getfd(int fd)
{
  // TODO
  // I have literally no idea how this is going to work. 
}

void *setfd(int fd, const char *data)
{
  // TODO
  // No idea about this one, either.
}

int *nextfd(void)
{
  // TODO
}

