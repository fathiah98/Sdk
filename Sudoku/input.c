#define _INPUT_C_
#include "input.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#define INPUTFILENAMME	"input.txt"
#define OUTPUTTFILENAMME	"output.txt"
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
void WriteResult()
{
	int i, j, k, l;
	char str[2];


	
	fpin = fopen(OUTPUTTFILENAMME, "wt");

	if (fpin != NULL)
	{
		for (i = 0; i < NUMS_IN_DIM; i++)
		{
			for (j = 0; j < NUMS_IN_DIM; j++)
			{
			//	sprintf(str, "%d", map[i][j]);
				fprintf(fpin, "%d ",map[i][j]);
				//fputc(" ", fpin);
			}
		}
		fclose(fpin);
	}
}