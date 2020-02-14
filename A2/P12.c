/*******************************************************
Loui Zibdawi							A2 - P12

0924538									Feb. 12th, 2017

CIS 3490								

********************************************************/

/*
This program counts the number of inversions in an Array 
using a divide-and-conquer approach. The efficiency class is O(n^2)
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h> 

int divideArray(int A[50000], int a, int b);

int numInversions(int A[50000], int start, int end);

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

	size--;

	ftime(&start);
	int num = divideArray(A, 0, size-1);
	ftime(&end);

	diff = (int) (1000.0 * (end.time - start.time) 
		+ (end.millitm - start.millitm));

	printf("Number of inversions: %d\n", num);
	printf("Execution time is: %d Milliseconds\n", diff);

	fclose(fp);

	return 0;
}

int divideArray(int A[50000], int a, int b)
{
	int mid, front, back, total;

	if(a>=b)
		return 0;

	mid = (a+b)/2;

	front = divideArray(A, a, mid);

	back = divideArray(A, mid+1,b);

	total = numInversions(A, a, b);

	return front + back + total;

}

int numInversions(int A[50000], int start, int end)
{
	int mid = (start+end)/2;
	int first = start;
	int second = mid+1, num = 0, a =0;
	int A2[end-start+1];

	do
	{
		if(A[first]<=A[second])
			A2[a++] = A[first++];
		else
		{
			A2[a++] = A[second++];
			num = num + mid - first + 1;
		}
	}while(first<=mid && second<=end);

	for(int j = first; j<=mid; j++)
		A2[a++] = A[j];

	for(int j = second; j<=end; j++)
		A2[a++] = A[j];

	for(int j = 0; j<end-start+1; j++)
		A[j+start] = A2[j];

	return num;
}
