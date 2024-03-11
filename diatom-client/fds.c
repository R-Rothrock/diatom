// fd.c
// handling file descriptiors

// okay, so this is going to have to have a sort of database system
// preferably in memory.
// How?
// We shall simply ("simply?" heh, no) use SQLite to create a
// "transient in-memory database."


enum fd_type {
  FD_TYPE_FILE,
  // TODO
} __attribute__((packed));

struct fd {
  enum fd_type type;
  char *loc;
  char *realloc;
}

struct fd *getfd(int fd)
{
  // TODO
}

void *setfd(int fd, struct fd *data)
{
  // TODO
}

int *nextfd(void)
{
  // TODO
}

