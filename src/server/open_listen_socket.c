#include "../server.h"

static struct addrinfo getHints() {
  struct addrinfo hints;

  memset(&hints, 0, sizeof(struct addrinfo));

  // Accept connections from any address.
  hints.ai_flags = AI_PASSIVE;

  // Accept either IPv4 or IPv6 connections.
  hints.ai_family = AF_UNSPEC;

  // TCP uses stream sockets.
  hints.ai_socktype = SOCK_STREAM;

  // Allow any protocol to be returned by getaddrinfo().
  hints.ai_protocol = 0;

  hints.ai_addrlen = 0;

  hints.ai_addr = NULL;

  hints.ai_canonname = NULL;

  hints.ai_next = NULL;

  return hints;
}

static int getListenSocketFileDescriptor(const struct addrinfo* addressInfo) {
  const struct addrinfo* rp = NULL;

  int listenSocketFileDescriptor = -1;

  for (rp = addressInfo; rp != NULL; rp = rp->ai_next) {
    listenSocketFileDescriptor = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

    if (listenSocketFileDescriptor == -1) {
      continue;
    }

    if (bind(listenSocketFileDescriptor, rp->ai_addr, rp->ai_addrlen) == 0) {
      break;
    }
  }

  if (rp == NULL) {
    perror("socket() or bind()");

    exit(EXIT_FAILURE);
  }

  return listenSocketFileDescriptor;
}

int openListenSocket(const char* port) {
  struct addrinfo hints = getHints();

  struct addrinfo* addressInfo = NULL;

  int getaddrinfoError = getaddrinfo(NULL, port, &hints, &addressInfo);

  if (getaddrinfoError != 0) {
    fprintf(stderr, "%s\n", gai_strerror(getaddrinfoError));

    exit(EXIT_FAILURE);
  }

  int listenSocketFileDescriptor = getListenSocketFileDescriptor(addressInfo);

  freeaddrinfo(addressInfo);

  if (listen(listenSocketFileDescriptor, 65535) != 0) {
    perror("listen()");

    exit(EXIT_FAILURE);
  }

  return listenSocketFileDescriptor;
}
