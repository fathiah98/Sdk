#include <stdio.h>
#include "common.h"
#include "data.h"
#include "datalogger.h"
#include "logic.h"
#include "display.h"
#include "input.h"

void main()
{
	int count = 1;
	int i, j = 0;

	InitData();
	ReadInput();
	CreateGivenDigitsVectors();
	initLogger();
	ShowQuestion();
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
		WriteResult();
	}
	else
	{
		printf("Cannot find a solution!\n");
	}

}



