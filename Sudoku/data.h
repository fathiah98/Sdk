
typedef struct Candidate
{
	int numbers[9];
	int count;
	int coord[9][2];
	struct Candidate *next;
};
typedef struct Candidate CandidateList;
