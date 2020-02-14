/*******************************************************
Loui Zibdawi                            A3 - P22.c

0924538                                 Mar. 9th, 2017

CIS 3490                                

********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h> 

void horspoolSearchForPattern(int sT[], char str[], char line[44049][100]);

void shiftTable(int sT[], char str[]);

int main()
{
    struct timeb start, end;                          
    int diff;                                               

    FILE* fp = fopen("data_5.txt", "r");
    char line[44049][100];
    char str[50];
    int sT[400];
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

    shiftTable(sT, str);
    ftime(&start);
    horspoolSearchForPattern(sT, str, line);
    ftime(&end);

    diff = (int) (1000.0 * (end.time - start.time) 
        + (end.millitm - start.millitm));

    printf("Execution time is: %d Milliseconds\n", diff);

    fclose(fp);
}
/*
*Creates a shift table with the number of elements to the right of each character
*and max value if the character isn't in the user entered string
*/
void shiftTable(int sT[], char str[])
{
    int m = strlen(str)-1;
    int size = 400;
    for(int i = 0; i<size-1; i++)
    {
        sT[i] = m;
    }
    for(int j = 0; j<m-1;j++)
    {
        int index = str[j] - 32;
        sT[index] = m-1-j;
    }
}
/*
*This function uses a horspool algorithm to search for a pattern which was
*given by the user, in a 2d array that holds the strings from the file data_5.txt
*/
void horspoolSearchForPattern(int sT[], char str[], char line[44049][100])
{
    int found = 0, count = 0, patternShift = 0, numRight = 0, flag =0;
    int m = strlen(str)-1;

    for(int i = 0; i<44049; i++)
    {
        int n = strlen(line[i]);

        if(strlen(str) <= strlen(line[i])) //If the pattern is shorter or equal to the size of the line
        {
            int j = 0;
            while(j<n-m) //Looking through the line
            {
                patternShift++;
                count = 0;
                numRight = 0;
                int k;
                for(k =m-1; k>=0; k--)
                {
                    if(line[i][j+k] == str[k])
                    {
                        if(flag != 1)
                            numRight++;
                        count++;
                    }
                    else
                        flag = 1;
                }
                k = m - 1 - numRight;
                if(count == m)
                {
                    found++;
                }
                int index = (unsigned char)line[i][j+k] - 32; //Last character read
                j = j + sT[index];
                //patternShift++;
            }
        }
    }

    printf("----------------------\n");
    printf("Horspool Algorithm\n");
    printf("----------------------\n");
    printf("%d occurences of %s\n", found, str);
    printf("Number of pattern shifts: %d\n", patternShift);
}
