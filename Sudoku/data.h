#ifdef _DATA_C_
#define EXTERN
#else
#define EXTERN extern
#endif
typedef struct candidate Candidate;
typedef struct candidate
{
	int numbers[3][3];
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

EXTERN Searchspace searchspace[3][3];

#ifdef _DATA_C_
int box[3][3][3][3] =
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

int map[9][9] =
{
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
	{ -1, -2, -3, -4, -5, -6, -7, -8, -9 },
};

#else
EXTERN int box[3][3][3][3];
EXTERN int map[9][9];
#endif

EXTERN Candidate* NewCandidate(int numbers[][3]);
EXTERN void InitData();
EXTERN void InsertCandidate(Candidate *ptr, int boxcoord[2]);
EXTERN void DeleteCandidate(Candidate *ptr, int boxcoord[2]);
EXTERN void VerifyList(Searchspace searchspace);

//int matchseq[3][2] = {{0,1}, {1,2}, {0,2}};
EXTERN Candidate *poss[3][3];
