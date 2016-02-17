#pragma once

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"

typedef int (*PlugInitFunction)();

typedef int (*PlugProcessFunction)(Request* request);

typedef struct Plug_t {
  char* name;
  void* libHandle;
  PlugInitFunction initFunction;
  PlugProcessFunction process;
} Plug;

int loadPlug(Plug* plug, const char* name);

int freePlug(Plug* plug);
