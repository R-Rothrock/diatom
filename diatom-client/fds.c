// fds.c
// handling file descriptiors

// okay, so this is going to have to have a sort of database system
// preferably in memory.
// How?
// We shall simply ("simply?" heh, no) use SQLite to create a
// "transient in-memory database." In this database we will store the
// data of the file descriptors.

#include <sqlite.h>

enum fd_type {
  FD_TYPE_FILE,
  // TODO
} __attribute__((packed));

struct fd {
  enum fd_type type;
  char *loc;
  char *realloc;
}

static sqlite3 *DB;

static char SQL_INIT_CMD[128] = "\
CREATE TABLE fds (\
id      INTEGER PRIMARY KEY AUTOINCREMEMT NOT NULL,\
type    TEXT NOT NULL,\
loc     TEXT NOT NULL,\
realloc TEXT NOT NULL,\
);"

    static char SQL_INSERT_CMD[64] = "\
INSERT INTO fds (id, type, loc, realloc)\
VALUES (%s, %s, %s, %s);"

    static char SQL_FETCH_CMD[64] = "\
SELECT *\
FROM fds\
WHERE id = %s;"

    static char SQL_NEXTFD_CMD[32] = "\
SELECT MAX(id) FROM fds;

    int
    fds_init(void) {
  /* run this before all other functions here */

  int ret;

  ret = sqlite3_open(":memory:", DB);

  if (ret != 0) {
    return ret;
  }

  ret = sqlite3_exec(&SQL_INIT_CMD, &DB);

  // TODO
}

int fds_exit(void) {
  /* run this after all other functions here */

  return sqlite3_close(DB);
}

struct fd *getfd(int fd) {
  // TODO
}

void *setfd(int fd, struct fd *data) {
  // TODO
}

void *clsfs(int fd) {
  // TODO
}

int *nextfd(void) {
  // TODO
}
