#pragma once

#include <stdlib.h>
#include "../plug.h"
#include "../request.h"

int testPlugInit(Plug* plug);

int process(Request* request);
