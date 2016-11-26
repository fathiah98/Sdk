#ifdef _DATALOGGER_C_
#define EXTERN
#else
#define EXTERN extern
#endif

//#define _CRT_SECURE_NO_WARNINGS

EXTERN void initLogger(void);

EXTERN void WriteCandidate(Candidate *ptr);
EXTERN void WriteString(char *str);
EXTERN void WriteSearchSpace(int row, int col);