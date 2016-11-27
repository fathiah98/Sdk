#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "common.h"
#include "data.h"
#ifndef _DISPLAY_C_
#define EXTERNDISPLAY extern
#else
#define EXTERNDISPLAY 
#endif

EXTERNDISPLAY void ShowSolution();
EXTERNDISPLAY void ShowQuestion();

#endif

