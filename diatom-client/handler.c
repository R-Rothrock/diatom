// handler.c
// https://github.com/R-Rothrock/diatom

#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "deps.h" /* dscp_port */

static int SOCKFD;
static struct sockaddr_in SERVER_ADDR;

in_addr_t get_central_ip(); // TODO

int handler_init() {
#define CATCH(x)                                                               \
  {                                                                            \
    if (!x)                                                                    \
      return -1;                                                               \
  }
  /* 0 on success, -1 on error. */

  SOCKFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  CATCH(SOCKFD);

  SERVER_ADDR.sin_family = AF_INET;
  SERVER_ADDR.sin_port = htons(2000);
  SERVER_ADDR.sin_addr.s_addr = inet_addr(get_central_ip());
}

int sendto_central(void *packet) {
  struct sockaddr *servaddr = (struct sockaddr *)&SERVER_ADDR;
  return sendto(SOCKFD, packet, sizeof(packet), 0, (struct sockaddr *)&servaddr,
                sizeof(&servaddr));
}

void *recvfrom_central() {
  // TODO
}
