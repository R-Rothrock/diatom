// handler.h
// https://github.com/R-Rothrock/diatom

#include "deps.h"

void *get_req()
{
  // TODO
}

int send_req()
{
  // TODO
}

int handle_request(int sockfd)
{
  void *buf = get_req();

  enum dicp_req req_type = ident_dicp(buf);
  switch(req_type)
  {
    // TODO
  }
}