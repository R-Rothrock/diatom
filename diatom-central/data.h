// data.h
// https://github.com/R-Rothrock/diatom
// persistent data storage

#ifndef DATA_H_
#define DATA_H_

#include<sqlite3.h>

/*****
 The following definitions are used by `handler.h`
*****/

// stores info necessary to identify and connect to a node on the network.
struct node_info;

// gets info from the SQLite database that stores node information.
struct node_info **get_node_info(char *pathname[]);

// path to database
#define NODE_INFO_DB "/etc/diatom/node_info.db"


/*****
 The following definitions don't exist yet.
*****/

#endif /* DATA_H_ */
