#ifndef _DATALOGGER_H_
#define _DATALOGGER_H_
#ifdef _DATALOGGER_C_
#define EXTERNDATALOGGER
#else
#define EXTERNDATALOGGER extern
#endif

//#define _CRT_SECURE_NO_WARNINGS

EXTERNDATALOGGER void initLogger(void);

EXTERNDATALOGGER void WriteCandidate(Candidate *ptr);
EXTERNDATALOGGER void WriteString(char *str);
EXTERNDATALOGGER void WriteSearchSpace(int row, int col);

#endif