#ifndef _INPUT_H_
#define _INPUT_H_

#include "common.h"

#ifndef _INPUT_C_
#define EXTERNINPUT extern
#else
#define EXTERNINPUT
#endif

EXTERNINPUT void ReadInput(void);

#endif