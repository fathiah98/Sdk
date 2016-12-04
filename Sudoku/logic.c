#define _LOGIC_C_
//#include "common.h"
#include "data.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
//#define PRINT_PERMUTATIONS

/*
	CreateGivenDigitsVectors() examines the puzzle. 
	It then fills up givenrownumbers[][] and givencolnumbers[][] with the fixed numbers given in the puzzle.
*/
void CreateGivenDigitsVectors()
{
	int i = 0;
	int boxrow = 0;
	int boxcol = 0;
	int row = 0;
	int col = 0;

	/* Searches the rows first */
	for (boxrow = 0; boxrow < DIM; boxrow++)
	{
		for (row = 0; row < DIM; row++)
		{
			for (boxcol = 0; boxcol < DIM; boxcol++)
			{
				for (col = 0; col < DIM; col++)
				{
					if (box[boxrow][boxcol][row][col] > 0)
					{
						givenrownumbers[boxrow * 3 + row][box[boxrow][boxcol][row][col]] = box[boxrow][boxcol][row][col]; // mark the appropriate index with the value of the number provided
					}
				}
			}
		}
	}
	/* Search the columns */
	for (boxcol = 0; boxcol < DIM; boxcol++)
	{
		for (col = 0; col < DIM; col++)
		{
			for (boxrow = 0; boxrow < DIM; boxrow++)
			{
				for (row = 0; row < DIM; row++)
				{
					if (box[boxrow][boxcol][row][col] > 0)
					{
						givencolnumbers[boxcol * 3 + col][box[boxrow][boxcol][row][col]] = box[boxrow][boxcol][row][col];
					}
				}
			}
		}
	}

}

/*
	Create a box of data given an array of missing numbers, and the original fixed set of numbers.
	Combines given numbers and a set of missing numbers correctly to form a candidate.
*/
void CreateBoxData(int results[], int boxdata[][3])
{
	int i, j = 0;
	int count = 0;

	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			boxdata[i][j] = box[boxcoord[0]][boxcoord[1]][i][j];	// Fill in the fixed value
			if (boxdata[i][j] == 0)
			{
				boxdata[i][j] = results[count++];					// Fill in a missing number
			}
		}
	}
}

/*
	FindMissing()  goes through a 2-dimensional array of DIM x DIM and finds
	the list of numbers that are missing. It writes the missing numbers into an output array (output[])
	and updates the missingcount variable which is passed into the function by reference.
*/
void FindMissing(int input[DIM][DIM], int output[], int *missingcount)
{
	int row = 0;
	int column = 0;
	int i = 0;
	int temp[NUMS_IN_DIM];
	*missingcount = 0;		// before search reset the missing count

	// initialize the search. Clears output[] and temp[].
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
				temp[input[row][column] - 1] = -1; // Use the array temp to mark which numbers are present. if say 3 is present, then temp[3-1] = -1.
			}
		}
	}
	for (i = 0; i < NUMS_IN_DIM; i++)
	{
		if (temp[i] != -1)
		{
			output[*missingcount] = i + 1;	// For every occurence of 0 in the temp, use the index of that 
											// location and derive the missing number by adding 1, then add 
											// the missing number to the list. 
			(*missingcount)++;				// increment number of missing numbers
		}
	}
}

/*
  FindMissingIndices()

  Given a box of numbers DIM x DIM, search it and record every instances where the box[i][j] is 0.
  Record all {x,y}s in output[][].
*/
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

/*
	This is an important function.

	Permutate() calls itself recursively to potentially generate all possible permutations of the numbers given in input[].
	The number of integers in the input[] array is given in ninput.
	currindex starts at 0, but increments everytime Permutate() calls itself.
	count records the number of permutations as they are found.

	An optimization is made so that not all permutations are generated. The recursive nature of the function calls makes the
	generation of permutations akin to that of walking a variable node tree. So it is possible to ignore, or do not generate 
	entire branches	if it is found that a number at the current position violates the puzzle.
*/
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
			if (CheckExist(nextstage[currindex], currindex) == 0) // If in violation, do not generate the branch of numbers, go to next branch
			{
				Permutate(nextstage, ninput, currindex + 1, count);
			}
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
		results[i + 1] = input[ninput - 1];
		CreateBoxData(results, resultsbox);						// This is the "X,Y" permutation. Using the permutation of missing numbers and the 
																// existing given numbers, generate a full box.
		InsertCandidate(NewCandidate(resultsbox), boxcoord);	// This box is a candidate, insert candidate into searchspace[][] using boxccord[][]

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
		CreateBoxData(results, resultsbox);					// This is the Y,X permutation. Do the same as the above.
		InsertCandidate(NewCandidate(resultsbox), boxcoord);
	}
}
/*
	Does the integer in value exists. int i is the ith missing number of the box (starts from 0).
	Use givencolnumbers[][] and givenrownumbers[][] to determine if value already exists in its row 
	and column in the puzzle.
*/
unsigned char CheckExist(int value, int i)
{
	unsigned char results = 1;

	int row = missingindices[i][0];
	int col = missingindices[i][1];
	int boxrow = boxcoord[0];
	int boxcol = boxcoord[1];

	int ind_row = (boxrow*DIM) + row;
	int ind_col = (boxcol*DIM) + col;

	if ((givenrownumbers[ind_row][value] + givencolnumbers[ind_col][value]) == 0)
	{
		results = 0;
	}

	return(results);
}

/*
	Seeking to deprecate this function.
	Out of a possible N candidates of a searchspace[i][j]. Reduce looks at boxes that are in the rows
	and then the columns of the searchspace[i][j] to see if any of the numbers are in violation. 
	If so, delete the candidate.

	This function is now mostly taken care of by CheckExist within Permutate() and may be totally 
	deprecated.
*/
void Reduce(int coord[])
{
	Candidate *ptr = searchspace[coord[0]][coord[1]].candidates;
	Candidate *delptr;
	unsigned char failed = 0;
	int boxrow, boxcolumn, i, j;

	printf("\nReducing candidates for : [%d][%d] from %d\n", coord[0], coord[1], searchspace[coord[0]][coord[1]].count);
	printf("Final candidate count :        ");
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
							box[coord[0]][boxcolumn][i][2] == ptr->numbers[i][j])
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
			DeleteCandidate(delptr, coord);
			printf("%c%c%c%c%c%c%6d", 8, 8, 8, 8, 8, 8, searchspace[coord[0]][coord[1]].count);
			VerifyList(searchspace[coord[0]][coord[1]]);
		}
	}
}

/*
	This is an important function.

	Given a number of possible candidates in each searchspace[i][j], and each of the candidates does not violate
	the fixed numbers in other boxes, find a solution within seachspace[i][j] such that for all i,j, there are no
	violation of all numbers in all rows and columns.

	This is a tree walk implemented using recursive function calls. The tree structure can be viewed as having variable 
	number of nodes per tree level.

	Search() is used to start the traversal at the beginning of each row (col=0). Search() calls TraverseBox() to
	recursively traverse across multiple columns for each row.
*/
unsigned char Search()
{
	unsigned char results = 0;
	int row = 0;
	int col = 0;
	unsigned char done = 0;

	/*
		initialize poss[][] before the search starts
		poss[row][col] points to the head of the list of candidates
		in searchspace[i][j]
	*/
	for (row = 0; row < DIM; row++)
	{
		for (col = 0; col < DIM; col++)
		{
			poss[row][col] = searchspace[row][col].candidates;
		}
	}

	col = 0;
	row = 0;
	done = 0;
	while (!done) 
	{
		// while the root node (box )still has a valid candidate, 
		// and no total successful match across the ith box row, keep looping
		results = TraverseBox(row, col); /*ith box row, next column*/
		if (results == 0) 
		{
			// the search for the current row failed. reset the box data at map[row][col]
			// reset the poss[row][col] candidates to point to the head of the list of candidates at searchspace[row][col]
			// decrement row, and also move the previous column's candidate pointer to the next one in the candidate list.
			// Reset the previous box map as well. Get ready to restart the search at the previous row.
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
				// FAILURE ! No solution.
				done = 1;
			}
		}
		else
		{
			// Current row all searched and a possible solution found, go to next row.
			row++;
		}

		if (row >= DIM)
		{
			// SUCCESS ! Solution found.
			done = 1;
		}

	}
	return(results);
}

/*
	This is an important function.

	TraverseBox() implements the tree walk across the columns of a particular row required to search for a possible solution, 
	using the candidate lists in each searchspace[i][j]. where i,j <- 0...(DIM-1)

*/
unsigned char TraverseBox(int row, int col)
{
	int results = 0;
	unsigned int done = 0;
	//	int i, j;
	while (poss[row][col] != NULL && done == 0)
	{
		WriteToMap(poss[row][col], row, col);		// write the current candidate at poss[row][col] to the map[][] for verification
		results = IsCompatible();					// verify map[][]
		if (results == 1)							// If ok, go to the next column
		{
			if ((col + 1) < DIM) // because there are three boxes per row and column
			{
				//	poss[row][col + 1] = searchspace[row][col + 1].candidates;
				results = TraverseBox(row, col + 1);
				done = results;
				/*
				If there is no match in the child node, reset the child node start pointer to the beginning of the candidate list.
				Also reset the map space occupied by the previous candidate. Use the next candidate in the parent node.
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
		else // if not, select the next candidate at pos[row][col]
		{
			poss[row][col] = poss[row][col]->next;
		}
	}

	return(results);
}
/*

	WriteToMap() writes the DIM x DIM numbers of a candidate into the map at boxcoord[boxrow][boxcool]
	for verification.
*/
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

/*
	Clear all numbers in the box at [boxrow][boxcol] to 0.
*/
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

/*
	IsCompatible() checks all rows in the map[][] to ensure that if the numbers are non-zero, there are no repeats.
	Then if row checks are ok, it checks the columns.
*/
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
					map[i][k] != 0)
				{
					done = 1;
					results = 0; // check failed.
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
						results = 0; // check failed
					}
				}
			}
		}
	}
	return(results);
}
