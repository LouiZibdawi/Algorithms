/*******************************************************
Loui Zibdawi							A2 - P21

0924538									Feb. 12th, 2017

CIS 3490								

********************************************************/

/*
This program completes the convex hull problem using a brute force approach. 
The efficiency class is O(n^2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h> 

typedef struct Point
{
	double x;
	double y;
}Point;

void convexHull(Point P[30000], int n);

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
	convexHull(P, size);
	ftime(&end);

	diff = (int) (1000.0 * (end.time - start.time) 
		+ (end.millitm - start.millitm));

	printf("------Execution time is: %d Milliseconds------\n", diff);

	fclose(fp);

	return 0;

}

void convexHull(Point P[30000], int n)
{
	Point a;
	Point b;
	Point c;
	Point boundaryList[5000];
	int k = 0;

	for(int i = 0; i<n; i++) //All elements but the last one
	{
		for(int j = 0; j<n;j++) //All elements after i
		{
			if(i==j)
				continue;
			//printf("%d\n", j);
			int sign = 0;
			int boundaryLine = 1;
			a = P[i];
			b = P[j];

			double numA = b.y - a.y;
			double numB = a.x - b.x;
			double numC = a.x*b.y - a.y*b.x;

			for(int m = 0; m < n; m++) //Searching through all points
			{
				if(m == i || m == j)
					continue;
				c = P[m];

				double region = numA * c.x + numB * c.y - numC;

				if(sign != 0)
				{
					if(region > 0 && sign < 0)
					{
						boundaryLine = 0;
						break;
					}
					else if(region < 0 && sign > 0)
					{
						boundaryLine = 0;
						break;
					}
				}
				else
				{
					if(region > 0) //left side
						sign = 1;
					else if(region < 0) //right side
						sign = -1;

				}
			}
			int flag = 0, flag2 = 0;
			if(boundaryLine == 1)
			{
				//printf("A: %lf... %lf\nB: %lf...%lf\n", a.x, a.y, b.x, b.y);
				for(int i = 0; i<k;i++) //Checking for duplicates in the boundary list
				{
					if(boundaryList[i].x == a.x && boundaryList[i].y == a.y)
					{
						flag = 1;
					}
					else if (boundaryList[i].x == b.x && boundaryList[i].y == b.y)
					{
						flag2 = 1;
					}
					else if(a.x == b.x && a.y == b.y)
					{
						flag2 = 1;
						break;
					}
				}
				if(flag != 1)
				{
					boundaryList[k] = a;
					k++;
				}
				
				if(flag2 != 1)
				{
					boundaryList[k] = b;
					k++;
				}
			}

		}
	}

	for(int i = 0; i<k; i++)
		printf("%d: X: %2lf Y: %2lf\n", i, boundaryList[i].x, boundaryList[i].y);
}
