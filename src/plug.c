#include "plug.h"

int loadPlug(Plug* plug, const char* name) {
  size_t nameLength = strlen(name);

  plug->name = malloc(nameLength + 1);

  strcpy(plug->name, name);

  char* filePath = malloc(strlen("./plugs/lib") + nameLength + strlen("Plug.A.dylib") + 1);

  strcpy(filePath, "./plugs/lib");

  strcat(filePath, name);

  strcat(filePath, "Plug.A.dylib");

  plug->libHandle = dlopen(filePath, RTLD_NOW);

  free(filePath);

  if (plug->libHandle == NULL) {
    fprintf(stderr, "%s\n", dlerror());

    return 1;
  }

  char* initFunctionName = malloc(nameLength + strlen("PlugInit") + 1);

  strcpy(initFunctionName, name);

  strcat(initFunctionName, "PlugInit");

  plug->initFunction = (PlugInitFunction)(intptr_t)dlsym(plug->libHandle, initFunctionName);

  free(initFunctionName);

  if (plug->initFunction == NULL) {
    fprintf(stderr, "%s\n", dlerror());

    dlclose(plug->libHandle);

    return 1;
  }

  plug->initFunction(plug);

  return 0;
}

int freePlug(Plug* plug) {
  free(plug->name);

  dlclose(plug->libHandle);

  return 0;
}
