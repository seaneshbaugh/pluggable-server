#pragma once

#include <stdlib.h>
#include <time.h>
#include "../plug.h"
#include "../request.h"

int daytimePlugInit(Plug* plug);

int process(Request* request);
