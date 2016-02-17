#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "plug_manager.h"
#include "server.h"

int main(int argc, char** argv) {
  PlugManager* plugManager = NULL;

  initPlugManager(&plugManager);

  addPlug(plugManager, "daytime");

  int listenSocketFileDescriptor = openListenSocket("10000");

  // Need to handle signals here so we can actually gracefully shut down.
  handleRequests(listenSocketFileDescriptor, plugManager);

  freePlugManager(plugManager);

  return 0;
}
