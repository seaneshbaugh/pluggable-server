#include "test_plug.h"

#include <stdio.h>

#define EXPORT __attribute__((visibility("default")))

__attribute__((constructor))
static void initializer(void) {
  printf("[%s] initializer()\n", __FILE__);
}

__attribute__((destructor))
static void finalizer(void) {
  printf("[%s] finalizer()\n", __FILE__);
}

EXPORT int addOne(const int number) {
  return number + 1;
}
