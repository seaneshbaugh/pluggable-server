#include "request.h"

int initRequest(Request** request, char* rawData, size_t rawDataLength) {
  *request = (Request*)malloc(sizeof(Request*));

  if (request == NULL) {
    return 1;
  }

  (*request)->rawData = (char*)malloc(rawDataLength);

  if ((*request)->rawData == NULL) {
    free(request);

    return 1;
  }

  memcpy((*request)->rawData, rawData, rawDataLength);

  (*request)->processedData = NULL;

  (*request)->finished = 0;

  return 0;
}

int freeRequest(Request* request) {
  free(request->rawData);

  if (request->processedData != NULL) {
    free(request->processedData);
  }

  free(request);

  return 0;
}
