#include <stdio.h>
#include "data.h"
#define MAXCOMBI 9*8*7*6*5*4*3*2
#define PRINT_PERMUTATIONS
void FindMissing(int input[3][3], int output[], int *missingcount);
void Permutate(int input[], int ninput, int currindex, int *count);
void FindMissingIndices(int box[][3], int output[][2]);
void CreateBoxData(int results[], int box[][3]);
void Reduce(int coord[]);

//int searchspace[9][MAXCOMBI][9] = {0};
//int candidates[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

int missingindices[9][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int missing[9];
int missingcount = 0;
int boxcoord[2] = { 0,0 };

void main()
{
	int count = 1;
	int i, j = 0;

	InitData();
	for (i = 0; i < 3; i++)
	{
		boxcoord[0] = i;
		for (j = 0; j < 3; j++)
		{
			boxcoord[1] = j;
			FindMissing(box[boxcoord[0]][boxcoord[0]], missing, &missingcount);
			FindMissingIndices(box[boxcoord[0]][boxcoord[0]], missingindices);
			Permutate(missing, missingcount, 0, &count);
			VerifyList(searchspace[boxcoord[0]][boxcoord[1]], nsearchspace[boxcoord[0]][boxcoord[1]]);
			Reduce(boxcoord);
		}
	}
}
/*
	Given a box coordinates out of a possible [3][3], scan the four adjacent neighbours 
	to find out if we can reduce the search space in the currrent box. The currrent search 
	space candidate is rejected/deleted if a common number is found in an adjacent box.
*/
void Reduce(int coord[])
{
	Candidate *ptr = searchspace[coord[0]][coord[1]];
	Candidate *delptr;
	unsigned char failed = 0;
	int boxrow, boxcolumn, i, j;

	while (ptr != NULL)
	{
		failed = 0;

		for (boxcolumn = 0; boxcolumn < 3; boxcolumn++)
		{
			if (boxcolumn != coord[1])
			{
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						if (box[coord[0]][boxcolumn][i][0] == ptr->numbers[i][j] ||
							box[coord[0]][boxcolumn][i][1] == ptr->numbers[i][j] || 
							box[coord[0]][boxcolumn][i][2] == ptr->numbers[i][j] )
						{
							/* found a corresponding square in the same box row both the search space and the unfilled box 
							with the same number, fail the search delete the current search space.*/
							j = 3;
							i = 3;
							boxcolumn = 3;
							failed = 1;
						}
					}
				}
			}
		}
		/* If box row checking has failed do not bother checking column, else check adjacent columns. */
		if (failed == 0)
		{
			for (boxrow = 0; boxrow < 3; boxrow++)
			{
				if (boxrow != coord[0])
				{
					for (i = 0; i < 3; i++)
					{
						for (j = 0; j < 3; j++)
						{
							if (box[boxrow][coord[1]][0][j] == ptr->numbers[i][j] ||
								box[boxrow][coord[1]][1][j] == ptr->numbers[i][j] ||
								box[boxrow][coord[1]][2][j] == ptr->numbers[i][j])
							{
								/* found a corresponding square in the same box column both the search space and the unfilled box
								with the same number, fail the search delete the current search space.*/

								j = 3;
								i = 3;
								boxrow = 3;
								failed = 1;
							}
						}
					}
				}
			}
		}
		delptr = ptr;
		ptr = ptr->next;
		if (failed == 1)
		{
			DeleteCandidate(delptr,coord);
			VerifyList(searchspace[coord[0]][coord[1]], nsearchspace[coord[0]][coord[1]]);
		}
	}
}


unsigned char IsExistInOtherBoxes(int num, int boxcoord[])
{
	unsigned char results = 0;
	int box_row = 0;
	int box_column = 0;
	int num_row = 0; 
	int num_column = 0;


	return(results);
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
	int results[9];
	int resultsbox[3][3];

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
#ifdef PRINT_PERMUTATIONS
		printf("[%d] : ", (*count)++);
#endif		
		for (i = 0; i < (ninput - 2); i++)
		{
#ifdef PRINT_PERMUTATIONS
			printf("%d ", input[i]);
#endif
			results[i] = input[i];
		}
#ifdef PRINT_PERMUTATIONS
		printf("%d %d\n", input[ninput - 2], input[ninput - 1]);
#endif
		results[i] = input[ninput - 2];
		results[i+1] = input[ninput - 1];
		CreateBoxData(results, resultsbox);
		InsertCandidate(NewCandidate(resultsbox), boxcoord);
		
#ifdef PRINT_PERMUTATIONS
		printf("[%d] : ", (*count)++);
		for (i = 0; i < (ninput - 2); i++)
		{
			printf("%d ", input[i]);
		}
		printf("%d %d\n", input[ninput - 1], input[ninput - 2]);
#endif
		results[i] = input[ninput - 1];
		results[i + 1] = input[ninput - 2];
		CreateBoxData(results, resultsbox);
		InsertCandidate(NewCandidate(resultsbox), boxcoord);
	}
}

void CreateBoxData(int results[], int boxdata[][3])
{
	int i, j = 0;
	int count = 0;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			boxdata[i][j] = box[boxcoord[0]][boxcoord[1]][i][j];
			if (boxdata[i][j] == 0)
			{
				boxdata[i][j] = results[count++];
			}
		}
	}
}

