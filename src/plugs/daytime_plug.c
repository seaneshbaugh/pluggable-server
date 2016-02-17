#include "daytime_plug.h"

#define EXPORT __attribute__((visibility("default")))

__attribute__((constructor))
static void initializer(void) {
}

__attribute__((destructor))
static void finalizer(void) {
}

EXPORT int daytimePlugInit(Plug* plug) {
  plug->process = process;

  return 0;
}

int process(Request* request) {
  // This might cause a memory leak if this plug is loaded after others.
  time_t timer;

  time(&timer);

  struct tm* localTime;

  localTime = localtime(&timer);

  char timeBuffer[26];

  strftime(timeBuffer, 26, "%Y:%m:%d %H:%M:%S", localTime);

  request->processedData = malloc(strlen(timeBuffer));

  strcpy(request->processedData, timeBuffer);

  request->finished = 1;

  return 0;
}
