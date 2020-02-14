/*******************************************************
Loui Zibdawi                            A3 - P21.c

0924538                                 Mar. 9th, 2017

CIS 3490                                

********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h> 

void bruteForceSearchForPattern(char str[], char line[44049][100]);

int main()
{
    struct timeb start, end;                          
    int diff;                                               

    FILE* fp = fopen("data_5.txt", "r");
    char line[44049][100];
    char str[50];
    int count = 0;

    //Reading in file to array
    while (!feof(fp))
    {
        fgets(line[count], 100, fp);
        count++;
    }
    
    do
    {
        printf("Enter a string: ");
        fgets(str, sizeof(str), stdin);
    }while(strlen(str) < 2);

    ftime(&start);
    bruteForceSearchForPattern(str, line);
    ftime(&end);

    diff = (int) (1000.0 * (end.time - start.time) 
        + (end.millitm - start.millitm));

    printf("Execution time is: %d Milliseconds\n", diff);

    fclose(fp);
}
/*
*This function uses a brute force algorithm to search for a pattern which was
*given by the user, in a 2d array that holds the strings from the file data_5.txt
*/
void bruteForceSearchForPattern(char str[], char line[44049][100])
{
    int found = 0, count = 0, patternShift = 0;
    int m = strlen(str)-1;

    for(int i = 0; i<44049; i++)
    {
        int n = strlen(line[i]);

        if(strlen(str) <= strlen(line[i])) //If the pattern is shorter or equal to the size of the line
        {
            for(int j = 0; j<n-m; j++) //Looking through the line
            {
                patternShift++;
                count = 0;
                for(int k = 0; k<m;k++)
                {
                    if(line[i][j+k] == str[k])
                        count++;
                }
                if(count == m)
                {
                    found++;
                    //break;
                }
            }
        }
    }

    printf("----------------------\n");
    printf("Brute Force Algorithm\n");
    printf("----------------------\n");
    printf("%d occurences of %s\n", found, str);
    printf("Number of pattern shifts: %d\n", patternShift);
}

