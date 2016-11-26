#include <stdio.h>
#include "common.h"
#include "data.h"
#include "datalogger.h"

//#define PRINT_PERMUTATIONS
void FindMissing(int input[DIM][DIM], int output[], int *missingcount);
void Permutate(int input[], int ninput, int currindex, int *count);
void FindMissingIndices(int box[][DIM], int output[][PAIR]);
void CreateBoxData(int results[], int box[][3]);
void Reduce(int coord[]);
unsigned char Search();
unsigned char TraverseBox(int row, int col);
unsigned char IsCompatible();
void WriteToMap(Candidate *ptr, int boxrow, int boxcol);
void ResetMap(int boxrow, int boxcol);
void ShowSolution();
//unsigned char FindCandidate(int orgrow, int orgcol, int destrow, int destcol);


int missingindices[NUMS_IN_DIM][PAIR] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int missing[9];
int missingcount = 0;
int boxcoord[2] = { 0,0 };

void main()
{
	int count = 1;
	int i, j = 0;

	InitData();
	initLogger();
	for (i = 0; i < DIM; i++)
	{
		boxcoord[0] = i;
		for (j = 0; j < DIM; j++)
		{
			boxcoord[1] = j;
			FindMissing(box[boxcoord[0]][boxcoord[1]], missing, &missingcount);
			FindMissingIndices(box[boxcoord[0]][boxcoord[1]], missingindices);
			Permutate(missing, missingcount, 0, &count);
			VerifyList(searchspace[boxcoord[0]][boxcoord[1]]);
			Reduce(boxcoord);
			WriteSearchSpace(boxcoord[0],boxcoord[1]);
		}
	}
	if (Search() == 1)
	{
		ShowSolution();
	}
	else
	{
		printf("Cannot find a solution!\n");
	}

}
/*
	Given a box coordinates out of a possible [3][3], scan the four adjacent neighbours 
	to find out if we can reduce the search space in the currrent box. The currrent search 
	space candidate is rejected/deleted if a common number is found in an adjacent box.
*/
void Reduce(int coord[])
{
	Candidate *ptr = searchspace[coord[0]][coord[1]].candidates;
	Candidate *delptr;
	unsigned char failed = 0;
	int boxrow, boxcolumn, i, j;

	while (ptr != NULL)
	{
		failed = 0;

		for (boxcolumn = 0; boxcolumn < DIM; boxcolumn++)
		{
			if (boxcolumn != coord[1])
			{
				for (i = 0; i < DIM; i++)
				{
					for (j = 0; j < DIM; j++)
					{
						if (box[coord[0]][boxcolumn][i][0] == ptr->numbers[i][j] ||
							box[coord[0]][boxcolumn][i][1] == ptr->numbers[i][j] || 
							box[coord[0]][boxcolumn][i][2] == ptr->numbers[i][j] )
						{
							/* found a corresponding square in the same box row both the search space and the unfilled box 
							with the same number, fail the search delete the current search space.*/
							j = DIM;
							i = DIM;
							boxcolumn = DIM;
							failed = 1;
						}
					}
				}
			}
		}
		/* If box row checking has failed do not bother checking column, else check adjacent columns. */
		if (failed == 0)
		{
			for (boxrow = 0; boxrow < DIM; boxrow++)
			{
				if (boxrow != coord[0])
				{
					for (i = 0; i < DIM; i++)
					{
						for (j = 0; j < DIM; j++)
						{
							if (box[boxrow][coord[1]][0][j] == ptr->numbers[i][j] ||
								box[boxrow][coord[1]][1][j] == ptr->numbers[i][j] ||
								box[boxrow][coord[1]][2][j] == ptr->numbers[i][j])
							{
								/* found a corresponding square in the same box column both the search space and the unfilled box
								with the same number, fail the search delete the current search space.*/

								j = DIM;
								i = DIM;
								boxrow = DIM;
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
			VerifyList(searchspace[coord[0]][coord[1]]);
		}
	}
}


unsigned char Search()
{
// this is a variable node per level tree search.
	unsigned char results = 0;
	int row=0;
//	int j = 0;
	int col = 0;
	unsigned char done = 0;

	/*initialize poss[][] before the search starts*/
	for (row = 0; row < DIM; row++)
	{
		for (col = 0; col < DIM; col++)
		{
			poss[row][col] = searchspace[row][col].candidates;
		}
	}

	// ROW-WISE SEARCH -- start from box col 0
	col = 0;
	row = 0;
	done = 0;
	while(!done) // i <- box row, find solutions for all box rows
	{
		// while the root node (box )still has a valid candidate, 
		// and no total successful match across the ith box row, keep looping
		results = TraverseBox(row, col); /*ith box row, next column*/
		if(results == 0)
		{
			if (row > 0)
			{
				ResetMap(row, col);
				poss[row][col] = searchspace[row][col].candidates;
				row = row - 1;
				poss[row][DIM - 1] = poss[row][DIM - 1]->next;
				ResetMap(row, DIM - 1);
			}
			else
			{
				done = 1;
			}
		}
		else
		{
			row++;
		}

		if (row >= DIM)
		{
			done = 1;
		}
		
	}
	return(results);
}

unsigned char TraverseBox(int row, int col)
{
	int results = 0;
	unsigned int done = 0;
//	int i, j;
	while (poss[row][col] != NULL && done == 0)
	{
		WriteToMap(poss[row][col], row, col);
		results = IsCompatible();
		if(results == 1)
		{
			if ((col + 1) < DIM) // because there are three boxes per row and column
			{
//				poss[row][col + 1] = searchspace[row][col + 1].candidates;
				results = TraverseBox(row, col + 1);
				done = results;
				/* 
					If there is no match in the child node, reset the child node start pointer to the beginning of the candidate list.
				    Also reset the map space occupied by the previous candidate 
				*/
				if (results == 0)
				{
					poss[row][col + 1] = searchspace[row][col + 1].candidates;
					ResetMap(row, col + 1);
					poss[row][col] = poss[row][col]->next;
				}
			}
			else
			{
				done = 1;
			}
		}
		else
		{
			poss[row][col] = poss[row][col]->next;
		}
	}

	return(results);
}

void WriteToMap(Candidate *ptr, int boxrow, int boxcol)
{
	int i;
	int j;

	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			map[boxrow * DIM + i][boxcol * DIM + j] = ptr->numbers[i][j];
		}
	}
	
}

void ResetMap(int boxrow, int boxcol)
{
	int i;
	int j;

	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			map[boxrow * DIM + i][boxcol * DIM + j] = 0;
		}
	}

}


unsigned char IsCompatible()
{
	int results = 1;
	int i = 0;
	int j = 0;
	int k = 0;
	unsigned char done = 0;
	/* checking the rows */
	for (i = 0; (i < NUMS_IN_DIM) && (done == 0); i++)
	{
		for (j = 0; (j < NUMS_IN_DIM - 1) && (done == 0); j++)
		{
			for (k = j + 1; (k < NUMS_IN_DIM) && (done == 0); k++)
			{
				if ((map[i][j] == map[i][k]) &&
					map[i][j] != 0 &&
					map[i][k] != 0 )
				{
					done = 1; 
					results = 0;
				}
			}
		}
	}
	/* Don't bother checking if the row check faiiled.*/
	if (results == 1)
	{
		/* checking the columns */
		for (i = 0; (i < NUMS_IN_DIM) && (done == 0); i++)
		{
			for (j = 0; (j < NUMS_IN_DIM - 1) && (done == 0); j++)
			{
				for (k = j + 1; (k < NUMS_IN_DIM) && (done == 0); k++)
				{
					if ((map[j][i] == map[k][i]) &&
						(map[j][i] != 0) &&
						(map[k][i] != 0))
					{
						done = 1;
						results = 0;
					}
				}
			}
		}
	}
	return(results);
}

/*
unsigned char FindCandidate(int orgrow, int orgcol, int destrow, int destcol)
{
	unsigned char results = 0;
	unsigned char done = 0;
	int i, j =0;
	Searchspace orgbox=searchspace[orgrow][orgcol];
	Searchspace destbox=searchspace[destrow][destcol];
	Candidate *orgptr = orgbox.current;
	Candidate *destptr = destbox.current;
	int matchcount = 0;

	while(done == 0)
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(orgptr->numbers[i][j] == destptr->numbers[i][0] ||
				   orgptr->numbers[i][j] == destptr->numbers[i][1] ||
				   orgptr->numbers[i][j] == destptr->numbers[i][2])
				{
					matchcount = 0;
					if(destptr->next != NULL)
					{
						destptr = destptr->next;
						i = -1; j = 3;
						destbox.current = destptr;
					}
					else
					{
						i=3;j=3;results = 0;
					}
				}

				else
				{
					matchcount++;
				}
			}
		}
		if(matchcount == 9)
		{
			done = 1;
			results = 1;
		}
	}
	return(results);
}
*/



void FindMissingIndices(int box[][3], int output[][2])
{
	int i = 0, j = 0;
	int outputcount = 0;

	for (i = 0; i < DIM; i++) // row
	{
		for (j = 0; j < DIM; j++) // column
		{
			if (box[i][j] == 0)
			{
				output[outputcount][0] = i;
				output[outputcount++][1] = j;
			}
		}
	}
}

void FindMissing(int input[DIM][DIM], int output[], int *missingcount)
{
	int row = 0;
	int column = 0;
	int i = 0;
	int temp[9];
	*missingcount = 0;

	for (i = 0; i < NUMS_IN_DIM; i++)
	{
		output[i] = 0;
		temp[i] = 0;
	}
	for (row = 0; row < DIM; row++)
	{
		for (column = 0; column < DIM; column++)
		{
			if (input[row][column] != 0)
			{
				temp[input[row][column]-1] = -1;
			}
		}
	}
	for (i = 0; i < NUMS_IN_DIM; i++)
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
	int nextstage[NUMS_IN_DIM];
	int results[NUMS_IN_DIM];
	int resultsbox[DIM][DIM];

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

	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			boxdata[i][j] = box[boxcoord[0]][boxcoord[1]][i][j];
			if (boxdata[i][j] == 0)
			{
				boxdata[i][j] = results[count++];
			}
		}
	}
}

void ShowSolution()
{
	int boxrow,boxcol,i,j;

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
		if ((i<NUMS_IN_DIM-1)&&((i + 1) % DIM == 0))
		{
			for (j = 0; j < 2 * (NUMS_IN_DIM + DIM); j++)
			{
				printf("-");
			}
			printf("\n");
		}
	}
}