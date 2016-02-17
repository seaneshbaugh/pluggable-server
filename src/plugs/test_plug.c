#include "test_plug.h"

#include <stdio.h>

#define EXPORT __attribute__((visibility("default")))

__attribute__((constructor))
static void initializer(void) {
}

__attribute__((destructor))
static void finalizer(void) {
}

EXPORT int testPlugInit(Plug* plug) {
  plug->process = process;

  return 0;
}

int process(Request* request) {
  request->processedData = malloc(5);

  strcpy(request->processedData, "test");

  request->finished = 1;

  return 0;
}
