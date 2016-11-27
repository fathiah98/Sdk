#ifndef _LOGIC_H_
#define _LOGIC_H_

#ifndef _LOGIC_C_
#define EXTERNLOGIC extern
#else
#define EXTERNLOGIC 
#endif

EXTERNLOGIC void Reduce(int coord[]);
EXTERNLOGIC unsigned char Search();
EXTERNLOGIC unsigned char TraverseBox(int row, int col);
EXTERNLOGIC unsigned char IsCompatible();
EXTERNLOGIC void WriteToMap(Candidate *ptr, int boxrow, int boxcol);
EXTERNLOGIC void ResetMap(int boxrow, int boxcol);
EXTERNLOGIC void FindMissing(int input[DIM][DIM], int output[], int *missingcount);
EXTERNLOGIC void Permutate(int input[], int ninput, int currindex, int *count);
EXTERNLOGIC void CreateBoxData(int results[], int box[][DIM]);
EXTERNLOGIC void CreateGivenDigitsVectors();
EXTERNLOGIC void FindMissingIndices(int box[][DIM], int output[][PAIR]);
EXTERNLOGIC unsigned char CheckExist(int value, int i);



#endif