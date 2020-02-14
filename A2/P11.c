/*******************************************************
Loui Zibdawi							A2 - P11

0924538									Feb. 12th, 2017

CIS 3490								

********************************************************/

/*
This program counts the number of inversions in an Array 
using a brute force approach. The efficiency class is O(n^2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h> 

void numInversions(int A[50000], int max);

int main(int argc, char* argv[])
{
	//Code for calculating time referenced from http://stackoverflow.com/questions/17250932/how-to-get-the-time-elapsed-in-c-in-milliseconds-windows
	struct timeb start, end;                          
    int diff;                                               

	if(argc != 2)
	{
		printf("The number of arguments include is wrong");
		exit(0);
	}

	FILE* fp;
	int A[50000];
	char* fileName;
	int size = 0;

	fileName = argv[1];

	fp = fopen(fileName, "r");

	while(!feof(fp))
	{
		fscanf(fp, "%d", &A[size]);
		size++;
	}

	ftime(&start);
	numInversions(A, size-1);
	ftime(&end);

	diff = (int) (1000.0 * (end.time - start.time) 
		+ (end.millitm - start.millitm));

	printf("Execution time is: %d Milliseconds\n", diff);

	fclose(fp);

	return 0;
}

void numInversions(int A[50000], int max)
{
	int numInversions = 0;

	for(int i = 0; i<max-1; i++)
	{
		for(int j = i+1; j<max;j++)
		{
			if(A[i]>A[j])
				numInversions++;
		}
	}

	printf("Number of inversions: %d\n", numInversions);
}