#include "plug_manager.h"

int initPlugManager(PlugManager** plugManager) {
  *plugManager = (PlugManager*)malloc(sizeof(PlugManager));

  const size_t initialPlugCapacity = 64;

  (*plugManager)->plugs = (Plug**)malloc(sizeof(Plug*) * initialPlugCapacity);

  (*plugManager)->numberOfPlugs = 0;

  (*plugManager)->plugCapacity = initialPlugCapacity;

  return 0;
}

int freePlugManager(PlugManager* plugManager) {
  for (size_t i = 0; i < plugManager->numberOfPlugs; i += 1) {
    freePlug(plugManager->plugs[i]);
  }

  free(plugManager->plugs);

  free(plugManager);

  return 0;
}

int addPlug(PlugManager* plugManager, const char* plugName) {
  if (plugManager->numberOfPlugs + 1 > plugManager->plugCapacity) {
    plugManager->plugs = realloc(plugManager->plugs, sizeof(Plug*) * plugManager->plugCapacity * 2);

    if (plugManager->plugs) {
      plugManager->plugCapacity *= 2;
    } else {
      return 1;
    }
  }

  Plug* plug = malloc(sizeof(Plug));

  loadPlug(plug, plugName);

  plugManager->plugs[plugManager->numberOfPlugs] = plug;

  plugManager->numberOfPlugs += 1;

  return 0;
}

int processRequest(PlugManager* plugManager, Request* request) {
  for (size_t i = 0; !request->finished && i < plugManager->numberOfPlugs; i += 1) {
    plugManager->plugs[i]->process(request);
  }

  return 0;
}
