#ifndef _DATA_H_
#define _DATA_H_

#include "common.h"

#ifdef _DATA_C_
#define EXTERNDATA
#else
#define EXTERNDATA extern
#endif

/*
	A candidate is defined as a DIMxDIM set of numbers with no blank elements.
	The next and previous pointers allow the creation of a doubly linked list.
	The doubly linked list enables insertion and deletion of candidates easily.
*/
typedef struct candidate Candidate;
typedef struct candidate
{
	int numbers[DIM][DIM];
	Candidate *next;
	Candidate *prev;
};

/* 
	A Searchspace is a data type defined to hold a list of candidates.
	It contains a count stating how many candidates are there in the list.
	The current pointer points to the currently used/access candidate.
	The candidates before the current pointer have been searched before and those 
	that come after have not been examined.	The current pointer can be reset to the 
	head of the list and the search restarted from beginning.
*/
typedef struct searchspace Searchspace;
typedef struct searchspace
{
	Candidate *candidates;
	int count;
	Candidate *current;
};


/*
A puzzle consists of DIM x DIM boxes.
Each box has DIM x DIM numbers.
A searchspace is a DIMxDIM 2-dimensional array of Searchspaces.
*/
EXTERNDATA Searchspace searchspace[DIM][DIM];


/*
The following are test input data. Deprecated because File I/O is now being used.
*/
#ifdef _DATA_C_
#if 0
int box[DIM][DIM][DIM][DIM] =
{
	/* 1st row */
	{
		{
			{ /*7*/0,      8, /*9*/0 },
			{      0/*4*/, 5, /*6*/0 },
			{ /*3*/0, /*1*/0,      2 }
		},
		{
			{      4, /*2*/0,      1 },
			{      3,      9, /*8*/0 },
			{ /*5*/0,      7, /*6*/0 }
		},
		{
			{ /*3*/0,  5,  /*6*/0 },
			{      1,  0/*7*/,  2 },
			{ /*8*/0,  9,       4 }
		}
	},

		/* 2nd row */
	{
		{
			{      2,      9,      1 },
			{ /*8*/0, /*6*/0,      7 },
			{      5, /*4*/0, /*3*/0 }
		},
		{
			{ 0/*7*/, /*4*/0,      3 },
			{ 0/*9*/,      1, /*5*/0 },
			{ 8,      /*6*/0,      2 }
		},
		{
			{ /*5*/0, /*6*/0,  /*8*/0 },
			{      2,      4,  /*3*/0 },
			{ /*7*/0, /*1*/0,  /*9*/0 }
		}
	},

		/* 3rd row */
	{
		{
			{ /*6*/0, 7, /*8*/0 },
			{ /*1*/0, 3,      4 },
			{      9, 2, /*5*/0 }
		},
		{
			{      1, /*3*/0, 4 },
			{      2, /*5*/0, 9 },
			{ /*6*/0,      8, 0/*7*/ }
		},
		{
			{ /*9*/0, 0/*2*/,      5 },
			{      6, 0/*8*/, /*7*/0 },
			{ /*4*/0, 0/*3*/,      1 }
		}
	}
};
#endif
#if 0
int box[DIM][DIM][DIM][DIM] =
{
	{
		{
			{ 0, 0, 2 },
			{ 5, 0, 0 },
			{ 0, 0, 0 }
		},
		{
			{ 0, 5, 9 },
			{ 0, 0, 0 },
			{ 0, 7, 1 }
		},
		{
			{ 0, 0, 0 },
			{ 0, 0, 7 },
			{ 4, 6, 0 }
		}
	},
	{
		{
			{ 6, 0, 0 },
			{ 0, 0, 3 },
			{ 9, 0, 0 }
		},
		{
			{ 8, 3, 0 },
			{ 0, 6, 0 },
			{ 0, 1, 2 }
		},
		{
			{ 0, 0, 9 },
			{ 8, 0, 0 },
			{ 0, 0, 4 }
		},

	},
	{
		{
			{ 0, 7, 6 },
			{ 4, 0, 0 },
			{ 0, 0, 0 }
		},
		{
			{ 1, 2, 0 },
			{ 0, 0, 0 },
			{ 3, 4, 0 }
		},
		{
			{ 0, 0, 0 },
			{ 0, 0, 1 },
			{ 5, 0, 0 }
		},
	}
};
#endif

#if 0
int box[DIM][DIM][DIM][DIM] =
{
	{
		{
			{ 0, 0, 0 },
			{ 0, 0, 6 },
			{ 0, 9, 0 }
		},
		{
			{ 0, 6, 3 },
			{ 9, 0, 5 },
			{ 0, 0, 0 }
		},
		{
			{ 0, 0, 0 },
			{ 7, 0, 0 },
			{ 0, 0, 0 }
		}
	},
	{
		{
			{ 0, 8, 3 },
			{ 4, 6, 0 },
			{ 1, 0, 0 }
		},
		{
			{ 0, 0, 6 },
			{ 0, 7, 0 },
			{ 3, 0, 0 }
		},
		{
			{ 0, 0, 7 },
			{ 0, 3, 8 },
			{ 4, 2, 0 }
		},

	},
	{
		{
			{ 0, 0, 0 },
			{ 0, 0, 1 },
			{ 0, 0, 0 }
		},
		{
			{ 0, 0, 0 },
			{ 8, 0, 7 },
			{ 4, 2, 0 }
		},
		{
			{ 0, 9, 0 },
			{ 5, 0, 0 },
			{ 0, 0, 0 }
		},
	}
};
#endif

int box[DIM][DIM][DIM][DIM] =
{
	{
		{
			{ 0, 0, 0 },
			{ 4, 0, 0 },
			{ 0, 0, 1 }
		},
		{
			{ 0, 0, 7 },
			{ 0, 5, 9 },
			{ 0, 2, 0 }
		},
		{
			{ 5, 9, 0 },
			{ 2, 0, 0 },
			{ 8, 0, 0 }
		}
	},
	{
		{
			{ 0, 0, 0 },
			{ 0, 6, 0 },
			{ 7, 0, 0 }
		},
		{
			{ 9, 7, 0 },
			{ 0, 4, 0 },
			{ 0, 6, 2 }
		},
		{
			{ 0, 0, 8 },
			{ 0, 7, 0 },
			{ 0, 0, 0 }
		},

	},
	{
		{
			{ 0, 0, 5 },
			{ 0, 0, 7 },
			{ 0, 1, 6 }
		},
		{
			{ 0, 9, 0 },
			{ 8, 1, 0 },
			{ 2, 0, 0 }
		},
		{
			{ 1, 0, 0 },
			{ 0, 0, 5 },
			{ 0, 0, 0 }
		},
	}
};

/*
The map is a DIM^2 x DIM^2 2-dimensional array of integers.
It is used as a scratch pad to form a partially solved puzzle.
Numbers are added one DIMxDIM box at a time. The whole map is then 
checked for violation. If there is a violation, the previous addition
of the box of numbers are cleared to 0's and the search restarted.
If there are no violations, the search proceeds to attempt to fill 
the next box.
*/
int map[NUMS_IN_DIM][NUMS_IN_DIM] =
{
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{  0,  0,  0,  0,  0,  0,  0,  0,  0 }
};


/*
The givenrownumbers is a 2-dimensional array of DIM^2 x DIM^2 integers.
It is the storage space used to mark which rows in the original puzzle has 
already been allocated a fixed number.

For example, if in the original puzzle, row 5 column 3 has a value 2,
then givenrownumbers[4][1] <- 2.
*/
int givenrownumbers[NUMS_IN_DIM][NUMS_IN_DIM + 1] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

/*
The givencolumnnumbers 2-dimensional array plays the same role as the givenrownumbers[][]
array, only now it is based on columns. For example, if the number in row 4 column 5 is a 3,
then givencolnumbers[5][4] <- 3.
*/
int givencolnumbers[NUMS_IN_DIM][NUMS_IN_DIM + 1] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int missingindices[NUMS_IN_DIM][PAIR] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
int boxcoord[PAIR] = { 0, 0 };
int missingcount = 0;
int missing[NUMS_IN_DIM];
#else
/*
Data that is uninitialized or will be dynamically initialized.
*/
EXTERNDATA int box[DIM][DIM][DIM][DIM];							// A puzzle. Comprises DIM^2 by DIM^2 numbers
EXTERNDATA int map[NUMS_IN_DIM][NUMS_IN_DIM];					// external reference to map which is defined in data.c
EXTERNDATA int givenrownumbers[NUMS_IN_DIM][NUMS_IN_DIM + 1];	// external reference to givenrownumbers which is defined in data.c
EXTERNDATA int givencolnumbers[NUMS_IN_DIM][NUMS_IN_DIM + 1];	// external reference to givencolnumbers whichc is defined in data.c
EXTERNDATA int missingindices[NUMS_IN_DIM][PAIR];				// missingindices is used to store the (row x col) coordinates of positions in a box that are empty 
EXTERNDATA int boxcoord[PAIR];									// The row X col tuple signifying the current box under analysis
EXTERNDATA int missingcount;									// records how many numbers are missing in a box
EXTERNDATA int missing[NUMS_IN_DIM];							// used to hold the vector of numbers missing from a box 
#endif

EXTERNDATA Candidate* NewCandidate(int numbers[][DIM]);						// Allocates memory for a new candidate
EXTERNDATA void InitData();													// Initialize searchspace to all point to NULL
EXTERNDATA void InsertCandidate(Candidate *ptr, int boxcoord[PAIR]);		// Insert a previously created and filled candidate struct into the head of the list in the searchspace array.
EXTERNDATA void DeleteCandidate(Candidate *ptr, int boxcoord[PAIR]);		// Delete a candidate pointed to by ptr from the searchspace array.
EXTERNDATA void VerifyList(Searchspace searchspace);						// Checks the integrity of a doubly linked list by traversing it forward and backwards. Verifying the number of elements in the list.

//int matchseq[3][2] = {{0,1}, {1,2}, {0,2}};
EXTERNDATA Candidate *poss[DIM][DIM];			// This array is used during the final search for solution given lists of reduced candidates in each box. 
												// Each element in poss[][] points to the currently used candidate.
												// It holds the current possible solution. It is the counterpart of map[][], using pointers to candidates.
#endif