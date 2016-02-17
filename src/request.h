#pragma once

#include <stdlib.h>
#include <string.h>

// This will change in the near future. I definitely want to keep the rawData
// field since at any point in the process a plug should be able to see it. What
// I probably will end up needing to do is change the proccessedData field to be
// some sort of loosely structured scratch space and then have a separate
// responseBody field. For now I'm sort of conflating the two. The finished
// field is sort of a hacky way of making sure a plug can stop any further plugs
// from being run. It's really hard for me to see how to do all of this wiht a
// high degree of certainty in C since I'm basically just passing pointers
// around. Worse, those pointers are crossing over into dynamically loaded
// libraries. That's kind of the point of this, but it makes it basically
// impossible to provide both safety and flexibility.
typedef struct Request_t {
  char* rawData;
  void* processedData;
  int finished;
} Request;

int initRequest(Request** request, char* rawData, size_t rawDataLength);

int freeRequest(Request*);
