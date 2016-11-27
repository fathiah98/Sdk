#define _DISPLAY_C_
#include "display.h"
#include <stdio.h>



void ShowSolution()
{
	int i, j;

	printf("\n\nSolution obtained :\n\n");
	for (j = 0; j < (NUMS_IN_DIM + DIM) * 2; j++)
	{
		printf("-");
	}
	printf("\n");

	for (i = 0; i < NUMS_IN_DIM; i++)
	{
		for (j = 0; j < NUMS_IN_DIM; j++)
		{
			printf("%d ", map[i][j]);
			if ((j + 1) % DIM == 0)
			{
				printf("| ");
			}
		}
		printf("\n");
		if ((i + 1) % DIM == 0)
		{
			for (j = 0; j < 2 * (NUMS_IN_DIM + DIM); j++)
			{
				printf("-");
			}
			printf("\n");
		}
	}
}

void ShowQuestion()
{
	int boxrow, boxcol, i, j;

	printf("Question Posed is : \n");
	for (j = 0; j < (NUMS_IN_DIM + DIM) * 2; j++)
	{
		printf("-");
	}
	printf("\n");

	for (boxrow = 0; boxrow < DIM; boxrow++)
	{
		for (i = 0; i < DIM; i++)
		{
			for (boxcol = 0; boxcol < DIM; boxcol++)
			{
				for (j = 0; j < DIM; j++)
				{
					if (box[boxrow][boxcol][i][j] > 0)
					{
						printf("%d ", box[boxrow][boxcol][i][j]);
					}
					else
					{
						printf("_ ");
					}
				}
				printf("| ");
			}
			printf("\n");
			if ((i + 1) % DIM == 0)
			{
				for (j = 0; j < (NUMS_IN_DIM + DIM) * 2; j++)
				{
					printf("-");
				}
				printf("\n");
			}
		}
	}
}