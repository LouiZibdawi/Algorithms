/*******************************************************
Loui Zibdawi							A2 - P22

0924538									Feb. 12th, 2017

CIS 3490								

********************************************************/

/*
This program completes the convex hull problem using a divide-and-conquer approach. 
The efficiency class is O(nlogn)
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h> 

typedef struct Point
{
	double x;
	double y;
}Point;

void startHull(Point P[30000], int n);

void findHull(Point P[30000], int n, Point c, Point d, Point *boundaryList, int* l);

int main(int argc, char* argv[])
{
	struct timeb start, end;                          
    int diff;                                               

	if(argc != 2)
	{
		printf("The number of arguments include is wrong\n");
		exit(0);
	}

	FILE* fp;
	char* fileName;
	int size = 0;
	Point P[30000];

	fileName = argv[1];

	fp = fopen(fileName, "r");

	if(fp == NULL)
	{
		printf("Error opening file\n");
		exit(0);
	}

	while(!feof(fp))
	{
		fscanf(fp, "%lf", &P[size].x);
		fscanf(fp, "%lf", &P[size].y);
		size++;
	}

	size--;

	ftime(&start);
	startHull(P, size);
	ftime(&end);

	diff = (int) (1000.0 * (end.time - start.time) 
		+ (end.millitm - start.millitm));

	printf("------Execution time is: %d Milliseconds------\n", diff);

	fclose(fp);

	return 0;

}

void startHull(Point P[30000], int n)
{
	if(P == NULL)
		return;

	Point a; //a is farthest left
	Point b ; //b is farthest right
	Point c;
	Point *boundaryList = malloc(sizeof(Point) * 500);
	int j = 0, k=0, l=0;

	int minX = P[0].x, minIndex = 0;
	int maxX = P[0].x, maxIndex = 0;

	for(int i = 0; i<n; i++) //All elements but the last one
	{
		if(P[i].x < minX) 
		{
			minX = P[i].x;
			minIndex = i;
		}
		else if(P[i].x > maxX)
		{
			maxX = P[i].x;
			maxIndex = i;
		}
	}

	a = P[minIndex];
	b = P[maxIndex];

	boundaryList[l] = a;
	//printf("%d: X: %2lf Y: %2lf\n", l, boundaryList[l].x, boundaryList[l].y);
	l++;
	boundaryList[l] = b;
	//printf("%d: X: %2lf Y: %2lf\n", l, boundaryList[l].x, boundaryList[l].y);
	l++;

	double numA = b.y - a.y;
	double numB = a.x - b.x;
	double numC = a.x*b.y - a.y*b.x;

	Point S1[30000];
	Point S2[30000];

	for(int m = 0; m < n; m++) //Searching through all points
	{
		c = P[m];

		double region = numA * c.x + numB * c.y - numC;

		if(region > 0) //right side(aka right of ab)
		{
			S1[k] = c;
			k++;
		}
		else if(region < 0) //left side (aka right of ba)
		{
			S2[j] = c;
			j++;
		}
	}

	// k--;
	// j--;
	findHull(S1, k, a, b, boundaryList, &l);
	findHull(S2, j, b, a, boundaryList, &l);

	for(int i = 0; i<l; i++)
		printf("%d: X: %2lf Y: %2lf\n", i, boundaryList[i].x, boundaryList[i].y);
}

void findHull(Point P[30000], int n, Point c, Point d, Point *boundaryList, int* l)
{
	//printf("hi\n");
	Point S1[30000];
	Point S2[30000];

	if(n < 2)
		return;
	Point e = P[0]; //Set to first element

	double numA = d.y - c.y;
	double numB = c.x - d.x;
	double numC = c.x*d.y - c.y*d.x;

	int maxRegion = numA * e.x + numB * e.y - numC;
	
	//FIND POINT FARTHEST FROM LINE
	for(int i = 0; i<n;i++) //All points in P
	{
		//Finding farthest of all points
		double region = numA * P[i].x + numB * P[i].y - numC;

		if(region > maxRegion)
		{
			maxRegion = region;
			e = P[i];
		}
	}
	//ADD THAT POINT TO THE BOUNDARY LIST
	int flag = 0;
	for(int i = 0; i<*l;i++) //Checking for duplicates in the boundary list
	{
		if(boundaryList[i].x == e.x && boundaryList[i].y == e.y)
		{
			flag = 1;
			break;
		}
	}
	if(flag != 1)
	{
		boundaryList[*l] = e;
		(*l)++;
	}

	//SEPERATE THE REST INTO S0, S1 or S2
	//Creating a region for C-E
	numA = e.y - c.y;
	numB = c.x - e.x;
	numC = c.x*e.y - c.y*e.x;
	//Creating a region for E-D
	double num1 = d.y - e.y;
	double num2 = e.x - d.x;
	double num3 = e.x*d.y - e.y*d.x;

	int j = 0, k = 0;
	for (int i = 0; i < n; i++)
	{
		double region = numA * P[i].x + numB * P[i].y - numC;
		double region2 = num1 * P[i].x + num2 * P[i].y - num3;

		if(region > 0) //right side of CE
		{
			S1[k] = P[i];
			k++;
		}
		else if(region2 > 0) //right side of ED
		{
			S2[j] = P[i];
			j++;
		}
	}
	// k--;
	// j--;
	findHull(S1, k, c, e, boundaryList, l);
	//printf("hi\n");
	findHull(S2, j, e, d, boundaryList, l);
}
