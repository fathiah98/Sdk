#define _DATALOGGER_H_
#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "datalogger.h"
#define FILENAME_LENGTH	20

FILE *fp;
char fname[FILENAME_LENGTH] = "logger.txt";

void initLogger()
{
	fp = fopen(fname, "wt");
	fclose(fp);
}


void WriteCandidate(Candidate *ptr)
{
	fp = fopen(fname, "a+t");
	fprintf(fp, "\t%d\t%d\t%d\n", ptr->numbers[0][0], ptr->numbers[0][1], ptr->numbers[0][2]);
	fprintf(fp, "\t%d\t%d\t%d\n", ptr->numbers[1][0], ptr->numbers[1][1], ptr->numbers[1][2]);
	fprintf(fp, "\t%d\t%d\t%d\n\n", ptr->numbers[2][0], ptr->numbers[2][1], ptr->numbers[2][2]);
	fclose(fp);
}

void WriteString(char *str)
{
	fp = fopen(fname, "a+t");
	fprintf(fp, "%s\n", str);
	fclose(fp);
}

void WriteSearchSpace(int row, int col)
{
	int i = 0;
	Candidate *ptr;
	fp = fopen(fname, "a+t");
	fprintf(fp, "Box : [%d,%d]\n",row,col);
	fprintf(fp, "count : %d\n", searchspace[row][col].count);
	fclose(fp);
	ptr = searchspace[row][col].candidates;
	while (ptr != NULL)
	{
		WriteCandidate(ptr);
		ptr = ptr->next;
	}
}