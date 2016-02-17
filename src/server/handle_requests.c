#include "../server.h"

void handleRequests(const int listenSocketFileDescriptor, PlugManager* plugManager) {
  int clients[MAX_CONNECTIONS];

  for (size_t i = 0; i < MAX_CONNECTIONS; i += 1) {
    clients[i] = -1;
  }

  size_t slot = 0;

  while (1) {
    struct sockaddr_in clientAddress;

    socklen_t clientAddressLength = 0;

    clients[slot] = accept(listenSocketFileDescriptor, (struct sockaddr*)&clientAddress, &clientAddressLength);

    if (clients[slot] < 0) {
      perror("accept()");
    } else {
      if (fork() == 0) {

        // This is awful. Need to figure out how to receive things in multiple chunks.
        char message[1025];

        memset((void*)message, (int)'\0', 1025);

        int received = recv(clients[slot], message, 1025, 0);

        if (received < 0) {
          fprintf(stderr, "recv() error\n");
        } else {
          if (received == 0) {
            fprintf(stderr, "Client disconnected uexpectedly\n");
          } else {
            // printf("%s", message);

            Request* request = NULL;

            initRequest(&request, message, received);

            processRequest(plugManager, request);

            write(clients[slot], request->processedData, strlen(request->processedData));

            freeRequest(request);
          }
        }

        shutdown(clients[slot], SHUT_RDWR);

        close(clients[slot]);

        clients[slot] = -1;

        exit(0);
      }
    }

    while (clients[slot] != -1) {
      slot = (slot + 1) % MAX_CONNECTIONS;
    }
  }
}
