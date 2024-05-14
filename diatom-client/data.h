// data.h
// persistent and runtime data storage

#include<arpa/inet.h> // `in_addr_t`

static char *DATA_PATH;

int data_init() {
  /* Locates conf file.
   * If you don't run this, whatever happens is your fault.
   */
  // TODO
}

in_addr_t *get_central_ip() {
  /* Gets central node IP from config file
   */
  // TODO
}

char *get_tmp_path() {
  /* Gets path for data storage
   */
  // TODO
