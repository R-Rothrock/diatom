// fds.c
// handling file descriptiors

// okay, so this is going to have to have a sort of database system
// preferably in memory.
// How?
// We shall simply ("simply?" heh, no) use SQLite3 to create a
// "transient in-memory database." In this database we will store the
// data of the file descriptors.

#include<stdbool.h>

#include <sqlite3.h>

/* `enum fd_type`: enumerating possible types of file descriptors */

enum fd_type {
  FD_TYPE_FILE, // i.e. files
  // TODO enumerate. duh.
} __attribute__((packed));

 
/* `struct fd`: how we store file descriptor information */
// enum fd_type type: the type of file descriptor
// char *loc: location on the central machine (i.e. a path)
// char *real_loc: location on this machine
// everything else might not be used, depending on the fd in question

// to clarify:
// fd.real_loc isn't actually the full path to the file. That's
// actually `fd.real_loc + fd.loc` if C supported string
// concatenation. For example, if on the central machine the file is
// `/usr/bin/grep`, and real_loc ends of being something like
// `$HOME/.diatom/files` or something of that nature (yet to be
// determined), then the full local files is
// `$HOME/.diatom/files/usr/bin/grep`

struct fd {
  enum fd_type type;
  char *loc;
  char *real_loc;
  int  flags; // i.e. O_READONLY
  int  index  // where we are in our data
  bool edited // whether or not the data has been edited
  // TODO add more where necessary
};

/* `static int NEXTFD`: keeping track of the next file descriptor */
// this value is to be edited over time, starting at 0, etc.
static int NEXTFD;

/* `static sqlite3 *DB`: the global access to our SQLite3 database */
static sqlite3 *DB;

/* A collection of SQLite commands to be used for handling the
 * SQLite database */
// SQL_INIT_CMD: used to initialize the table we'll be using in the
// database
// SQL_INSERT_CMD: used to add file descriptors into the table
// SQL_FETCH_CMD: used to fetch file descriptors from the table
// SQL_CLSFD_CMD: used to remove a file descriptor from the table

static char SQL_INIT_CMD[] = "\
CREATE TABLE fds (\
id      INTEGER PRIMARY KEY AUTOINCREMEMT NOT NULL,\
type    TEXT NOT NULL,\
loc     TEXT NOT NULL,\
real_loc TEXT NOT NULL,\
);"; // TODO make this inclusive of `struct fd`

static char SQL_INSERT_CMD[] = "\
INSERT INTO fds (id, type, loc, real_loc)\
VALUES (%s, %s, %s, %s);"; // TODO make this inclusive of `struct fd`

static char SQL_FETCH_CMD[] = "\
SELECT *\
FROM fds\
WHERE id = %s;";

static char SQL_CLSFD_CMD[] = "\
DELETE FROM fds\
WHERE id = %s;";

int fds_init(void) {
  /* Initializes the SQLite3 database in memory. So, yeah, kind of a
   * big deal. In other words, run this before anything else. */

  int ret;

  ret = sqlite3_open(":memory:", &DB);

  if (ret != 0) {
    return ret;
  }

  ret = sqlite3_exec(&SQL_INIT_CMD, &DB /* TODO linter says there's problems */);

  // TODO confirm all is well, return success
}

struct fd *getfd(int fd) {
  /* Gets file descriptor data from the SQLite3 database and hands it
   * to you via a `struct fd`. */
  // TODO
}

int setfd(int fd, struct fd *data) {
  /* Sets file descriptor data in the database. */
  // TODO
}

int clsfs(int fd) {
  /* Removes file descripter data from the database. Also removes
   * any associated data from the hard drive (`real_loc`). Needless
   * to say, be a bit careful with this lol. */ 
  // TODO
}

int get_nextfd(void) { return nextfd; }

int fds_exit(void) {
  /* Closes the SQLite3 database in memory. Before doing this, it
   * deletes all file descriptors via `clsfs` to ensure that all
   * respective data on the hard drive is unlinked. Run this after
   * everything with the SQLite3 database is done (and, on the same
   * note, make sure nothing is done after this function is called.
   * That'd be a pretty dumb segfault. */

  return sqlite3_close(DB);
}

