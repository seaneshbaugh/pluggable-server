#pragma once

#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX_CONNECTIONS 1024

int openListenSocket(const char* port);

void handleRequests(const int listenSocketFileDescriptor);
