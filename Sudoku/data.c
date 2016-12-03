#define _DATA_C_
#include "data.h"
#include <stdlib.h>
#include <stdio.h>

// Each box is 3x3 array of integers.

/*
	InitData() is to be called before any other functions in this file is used. 
	It clears the searchspace[][] array and any other data structures as required.
*/
void InitData()
{
	int i = 0, j = 0;

	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			searchspace[i][j].candidates = NULL;
			searchspace[i][j].count = 0;
			searchspace[i][j].current = NULL;
		}
	}
}

/* Allocate memory and initialize new struct with data */
Candidate* NewCandidate(int numbers[][3])
{
	int i = 0, j = 0;
	Candidate *ptr = (Candidate *)malloc(sizeof(Candidate));

	if (ptr != NULL)
	{
		for (i = 0; i < DIM; i++)
		{
			for (j = 0; j < DIM; j++)
			{
				ptr->numbers[i][j] = numbers[i][j];

			}
		}
		ptr->next = NULL;
		ptr->prev = NULL;
	}
	return(ptr);
}

/* Insert Candidate to the front of the list, given a seachspace coordinate pair */
void InsertCandidate(Candidate *ptr, int boxcoord[2])
{
//	Candidate *headptr = searchspace[boxcoord[0]][boxcoord[1]].candidates;
	ptr->next = searchspace[boxcoord[0]][boxcoord[1]].candidates;

	if (searchspace[boxcoord[0]][boxcoord[1]].candidates != NULL)
	{
		searchspace[boxcoord[0]][boxcoord[1]].candidates->prev = ptr;
	}

	searchspace[boxcoord[0]][boxcoord[1]].candidates = ptr;
	searchspace[boxcoord[0]][boxcoord[1]].count++;
	searchspace[boxcoord[0]][boxcoord[1]].current = ptr;
}

/* Delete the candidate from a particular searchspace[][] using a pointer to it */
void DeleteCandidate(Candidate *ptr, int coord[2])
{
	Candidate *prev_node = NULL;
	Candidate *next_node = NULL;
	if (ptr != NULL)
	{
		if (ptr->prev != NULL)
		{
			prev_node = ptr->prev;
			prev_node->next = ptr->next;
		}
		else
		{
			searchspace[coord[0]][coord[1]].candidates = ptr->next;
		}

		next_node = ptr->next;

		if (next_node != NULL)
		{
			next_node->prev = ptr->prev;
		}
		

		free(ptr);
		searchspace[coord[0]][coord[1]].count--;
		searchspace[coord[0]][coord[1]].current = searchspace[coord[0]][coord[1]].candidates;
	}
}

/*
	Traverse the doubly linked list to search for errors.
	Verify against recorded count of elements.
*/
void VerifyList(Searchspace searchspace)
{
	int nelem = 0;
	Candidate *lastptr = NULL;
	Candidate *ptr = searchspace.candidates;
	int count = searchspace.count;

	while (ptr != NULL)
	{
		lastptr = ptr;
		ptr = ptr->next;
		nelem++;
	}

	if (count != nelem)
	{
		printf("Fatal :: List number of element mismatch.\n");
	}
	
	ptr = lastptr;
	nelem = 0;
	while (ptr != NULL)
	{
		ptr = ptr->prev;
		nelem++;
	}

	if (count != nelem)
	{
		printf("Fatal :: Prev traverse :: List number of element mismatch.\n");
	}

}