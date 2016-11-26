#ifndef _DATA_H_
#define _DATA_H_
#include "common.h"
#ifdef _DATA_C_
#define EXTERN
#else
#define EXTERN extern
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

EXTERN Searchspace searchspace[DIM][DIM];

#ifdef _DATA_C_
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

#else
EXTERN int box[DIM][DIM][DIM][DIM];
EXTERN int map[NUMS_IN_DIM][NUMS_IN_DIM];
#endif

EXTERN Candidate* NewCandidate(int numbers[][DIM]);
EXTERN void InitData();
EXTERN void InsertCandidate(Candidate *ptr, int boxcoord[PAIR]);
EXTERN void DeleteCandidate(Candidate *ptr, int boxcoord[PAIR]);
EXTERN void VerifyList(Searchspace searchspace);

//int matchseq[3][2] = {{0,1}, {1,2}, {0,2}};
EXTERN Candidate *poss[DIM][DIM];
#endif