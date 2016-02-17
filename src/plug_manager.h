#pragma once

#include <stdlib.h>
#include "plug.h"

typedef struct PlugManager_t {
  Plug** plugs;
  size_t numberOfPlugs;
  size_t plugCapacity;
} PlugManager;

int initPlugManager(PlugManager** plugManager);

int freePlugManager(PlugManager* plugManager);

int addPlug(PlugManager* plugManager, const char* plugName);

int processRequest(PlugManager* plugManager, Request* request);
