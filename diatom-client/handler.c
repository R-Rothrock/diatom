// handler.c
// https://github.com/R-Rothrock/diatom

#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <data.h> /* get_central_ip */
#include <deps.h> /* dscp_port */

static int SOCKFD;
static struct sockaddr_in SERVER_ADDR;

int handler_init() {
  /* 0 on success, -1 on error. */

  SOCKFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  SERVER_ADDR.sin_family = AF_INET;
  SERVER_ADDR.sin_port = htons(2000);
  SERVER_ADDR.sin_addr.s_addr = inet_addr(get_central_ip());
}

int sendto_central(void *packet) {
  // TODO
}

void *recvfrom_central() {
  // TODO
}
