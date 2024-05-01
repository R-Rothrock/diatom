// fds.c
// handling file descriptiors

// okay, so this is going to have to have a sort of database system
// preferably in memory.
// How?
// We shall simply ("simply?" heh, no) use SQLite to create a
// "transient in-memory database." In this database we will store the
// data of the file descriptors.

#include <sqlite3.h>

enum fd_type {
  FD_TYPE_FILE,
  // TODO
} __attribute__((packed));

struct fd {
  enum fd_type type;
  int flags; // fd flags (for transparency with the kernel
  // TODO other usefull descriptive data here (if needed)
  int index;      // for, say, keeping track of where we are in a file
  char *loc;      // location on the central machine
  char *real_loc; // location on this machine (look at next comment)
};

// to clarify:
// fd.real_loc isn't actually the full path to the file. That's
// actually `fd.real_loc + fd.loc` if C supported string
// concatenation. For example, if on the central machine the file is
// `/usr/bin/grep`, and real_loc ends of being something like
// `~/.diatom/files` or something of that nature (yet to be
// determined), then the full local files is
// `$HOME/.diatom/files/usr/bin/grep`

int nextfd = 0;

static sqlite3 *DB;

static char SQL_INIT_CMD[] = "\
CREATE TABLE fds (\
id      INTEGER PRIMARY KEY AUTOINCREMEMT NOT NULL,\
type    TEXT NOT NULL,\
loc     TEXT NOT NULL,\
real_loc TEXT NOT NULL,\
);";

static char SQL_INSERT_CMD[] = "\
INSERT INTO fds (id, type, loc, real_loc)\
VALUES (%s, %s, %s, %s);";

static char SQL_FETCH_CMD[] = "\
SELECT *\
FROM fds\
WHERE id = %s;";

static char SQL_CLSFD_CMD[] = "\
DELETE FROM fds\
WHERE id = %s;";

int fds_init(void) {
  /* run this before all other functions here */

  int ret;

  ret = sqlite3_open(":memory:", &DB);

  if (ret != 0) {
    return ret;
  }

  ret =
      sqlite3_exec(&SQL_INIT_CMD, &DB /* TODO linter says there's problems */);

  // TODO
}

int fds_exit(void) {
  /* run this after all other functions here */

  return sqlite3_close(DB);
}

struct fd *getfd(int fd) {
  // TODO
}

int setfd(int fd, struct fd *data) {
  // TODO
}

int clsfs(int fd) {
  // TODO
  // this function will also wipe the locally stored data (real_loc)
}

int get_nextfd(void) { return nextfd; }
