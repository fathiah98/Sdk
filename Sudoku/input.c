#define _INPUT_C_
#include "input.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#define INPUTFILENAMME	"input.txt"
FILE *fpin = NULL;

void ReadInput()
{
	int i,j,k,l;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					box[i][j][k][l] = 0;
				}
			}
		}
	}
	fpin = fopen(INPUTFILENAMME, "rt");

	if (fpin != NULL)
	{
		for (i = 0; i < 9; i++)
		{
			fscanf(fpin, "%d %d %d %d %d %d %d %d %d", &(box[(i / 3)][0][i % 3][0]), &(box[(i / 3)][0][i % 3][1]), &(box[(i / 3)][0][i % 3][2]), &(box[(i / 3)][1][i % 3][0]), &(box[(i / 3)][1][i % 3][1]), &(box[(i / 3)][1][i % 3][2]), &(box[(i / 3)][2][i % 3][0]), &(box[(i / 3)][2][i%3][1]), &(box[(i / 3)][2][i % 3][2]));
		}
		fclose(fpin);
	}
}