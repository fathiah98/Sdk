#ifndef _SUDOKU_IO_H_
#define _SUDOKU_IO_H_

#include "common.h"

#ifndef _SUDOKU_IO_C_
#define EXTERNIO extern
#else
#define EXTERNIO
#endif

EXTERNIO void ReadInput(void);
EXTERNIO void WriteResult(void);
#endif