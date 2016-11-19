#include <stdio.h>
#include "data.h"
#define MAXCOMBI 9*8*7*6*5*4*3*2
void FindMissing(int input[3][3], int output[], int *missingcount);
void Permutate(int input[], int ninput, int currindex, int *count);
void FindMissingIndices(int box[][3], int output[][2]);

CandidateList *SearchSpace = NULL;

int box[9][3][3] = 
{
	{
		{ 9, 8, 0 },
		{ 0, 2, 3 },
		{ 0, 7, 0 }
	}
};

int searchspace[9][MAXCOMBI][9] = {0};

int candidates[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


void main()
{
	int missing[9];
	int missingcount = 0;
	int count = 1;
	int missingindices[9][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
	
	FindMissing(box[0], missing, &missingcount);
	FindMissingIndices(box[0], missingindices);
	Permutate(missing, missingcount, 0, &count);
}

void FindMissingIndices(int box[][3], int output[][2])
{
	int i = 0, j = 0;
	int outputcount = 0;

	for (i = 0; i < 3; i++) // row
	{
		for (j = 0; j < 3; j++) // column
		{
			if (box[i][j] == 0)
			{
				output[outputcount][0] = i;
				output[outputcount++][1] = j;
			}
		}
	}
}

void FindMissing(int input[3][3], int output[], int *missingcount)
{
	int row = 0;
	int column = 0;
	int i = 0;
	int temp[9];
	*missingcount = 0;

	for (i = 0; i < 9; i++)
	{
		output[i] = 0;
		temp[i] = 0;
	}
	for (row = 0; row < 3; row++)
	{
		for (column = 0; column < 3; column++)
		{
			if (input[row][column] != 0)
			{
				temp[input[row][column]-1] = -1;
			}
		}
	}
	for (i = 0; i < 9; i++)
	{
		if (temp[i] != -1)
		{
			output[*missingcount] = i + 1;
			(*missingcount)++;
		}
	}
}

void Permutate(int input[], int ninput, int currindex, int *count)
{
	int i = 0;
	int temp = 0;
	int nextstage[9];
	
	for (i = 0; i<ninput; i++)
	{
		nextstage[i] = input[i];
	}
	if ((ninput - currindex)>2)
	{

		for (i = currindex; i < ninput; i++)
		{
			temp = nextstage[currindex];
			nextstage[currindex] = nextstage[i];
			nextstage[i] = temp;
			Permutate(nextstage, ninput, currindex + 1, count);
		}
	}
	else
	{
		printf("[%d] : ", (*count)++);

		for (i = 0; i < (ninput - 2); i++)
		{
			printf("%d ", input[i]);
			searchspace[0][*count][i] = input[i];
		}
		printf("%d %d\n", input[ninput - 2], input[ninput - 1]);

		printf("[%d] : ", (*count)++);
		for (i = 0; i < (ninput - 2); i++)
		{
			printf("%d ", input[i]);
		}
		printf("%d %d\n", input[ninput - 1], input[ninput - 2]);
	}
}

