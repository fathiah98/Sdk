#ifndef _DATA_H_
#define _DATA_H_

#include "common.h"

#ifdef _DATA_C_
#define EXTERNDATA
#else
#define EXTERNDATA extern
#endif

typedef struct candidate Candidate;
typedef struct candidate
{
	int numbers[DIM][DIM];
//	int count;
	Candidate *next;
	Candidate *prev;
};

typedef struct searchspace Searchspace;
typedef struct searchspace
{
	Candidate *candidates;
	int count;
	Candidate *current;
};

EXTERNDATA Searchspace searchspace[DIM][DIM];

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
EXTERNDATA int box[DIM][DIM][DIM][DIM];
EXTERNDATA int map[NUMS_IN_DIM][NUMS_IN_DIM];
EXTERNDATA int givenrownumbers[NUMS_IN_DIM][NUMS_IN_DIM + 1];
EXTERNDATA int givencolnumbers[NUMS_IN_DIM][NUMS_IN_DIM + 1];
EXTERNDATA int missingindices[NUMS_IN_DIM][PAIR];
EXTERNDATA int boxcoord[PAIR];
EXTERNDATA int missingcount;
EXTERNDATA int missing[NUMS_IN_DIM];
#endif

EXTERNDATA Candidate* NewCandidate(int numbers[][DIM]);
EXTERNDATA void InitData();
EXTERNDATA void InsertCandidate(Candidate *ptr, int boxcoord[PAIR]);
EXTERNDATA void DeleteCandidate(Candidate *ptr, int boxcoord[PAIR]);
EXTERNDATA void VerifyList(Searchspace searchspace);

//int matchseq[3][2] = {{0,1}, {1,2}, {0,2}};
EXTERNDATA Candidate *poss[DIM][DIM];
#endif