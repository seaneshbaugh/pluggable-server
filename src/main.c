#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

typedef int (*FP)(int number);

int main(int argc, char** argv) {
  void* libHandle = dlopen("./plugs/libTestPlug.A.dylib", RTLD_NOW);

  if (libHandle == NULL) {
    fprintf(stderr, "%s\n", dlerror());

    exit(EXIT_FAILURE);
  }

  FP addOne = (FP)(intptr_t)dlsym(libHandle, "addOne");

  if (addOne == NULL) {
    fprintf(stderr, "%s\n", dlerror());

    dlclose(libHandle);

    exit(EXIT_FAILURE);
  }

  printf("1 + 1 = %d\n", addOne(1));

  dlclose(libHandle);

  int listenSocketFileDescriptor = openListenSocket("10000");

  handleRequests(listenSocketFileDescriptor);

  return 0;
}
