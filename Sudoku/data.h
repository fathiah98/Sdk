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

EXTERN Candidate *searchspace[3][3]; // 3x3 array of pointers. Each pointer corresponds to seach space for a box and contains a linked list of candidates
EXTERN int       nsearchspace[3][3];
#ifdef _DATA_C_
int box[3][3][3][3] =
{
	/* 1st row */
	{
		{
			{ 9, 8, 0 },
			{ 0, 2, 0 },
			{ 0, 7, 0 }
		},
		{
			{ 0, 7, 0 },
			{ 0, 0, 0 },
			{ 0, 0, 2 }
		},
		{
			{ 0, 0, 0 },
			{ 7, 0, 0 },
			{ 0, 0, 4 }
		}
	},

		/* 2nd row */
	{
		{
			{ 3, 0, 0 },
			{ 0, 0, 4 },
			{ 0, 0, 7 }
		},
		{
			{ 0, 2, 5 },
			{ 9, 0, 8 },
			{ 4, 6, 0 }
		},
		{
			{ 9, 0, 0 },
			{ 3, 0, 0 },
			{ 0, 0, 8 }
		}
	},

		/* 3rd row */
	{
		{
			{ 8, 0, 0 },
			{ 0, 0, 1 },
			{ 0, 0, 0 }
		},
		{
			{ 5, 0, 0 },
			{ 0, 0, 0 },
			{ 0, 8, 0 }
		},
		{
			{ 0, 9, 0 },
			{ 0, 2, 0 },
			{ 0, 6, 7 }
		}
	}
};

#else
EXTERN int box[3][3][3][3];
#endif



EXTERN Candidate* NewCandidate(int numbers[][3]);
EXTERN void InitData();
EXTERN void InsertCandidate(Candidate *ptr, int boxcoord[2]);
EXTERN void DeleteCandidate(Candidate *ptr, int boxcoord[2]);
