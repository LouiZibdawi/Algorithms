/*******************************************************
Loui Zibdawi                            A3 - P23.c

0924538                                 Mar. 9th, 2017

CIS 3490                                

********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h> 

void bmSearchForPattern(int bST[], int gST[], char str[], char line[44049][100]);

void badShiftTable(int sT[], char str[]);

void goodShiftTable(int sT[], char str[]);

void suffixes(char *x, int m, int *suff);

int main()
{
    struct timeb start, end;                          
    int diff;                                               

    FILE* fp = fopen("data_5.txt", "r");
    char line[44049][100];
    char str[50];
    int bST[400], gST[400];
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

    badShiftTable(bST, str);
    goodShiftTable(gST, str);
    ftime(&start);
    bmSearchForPattern(bST, gST, str, line);
    ftime(&end);

    diff = (int) (1000.0 * (end.time - start.time) 
        + (end.millitm - start.millitm));

    printf("Execution time is: %d Milliseconds\n", diff);

    fclose(fp);
}
/*
*Creates a shift table with the number of elements to the right of each character
*and num value if the character isn't in the user entered string
*/
void badShiftTable(int sT[], char str[])
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
*Creates a good shift table with the number of elements to the right of 
*each character and num value if the character isn't in the user entered string
*/
void goodShiftTable(int sT[], char str[])
{
    int size = strlen(str)-1, m = 0, j = 0, numRight = 0, count = 0;
    int suffixIndex = 0;
    char suffix[size];

    for(int i = size-1; i >=0; i--) //Initialize elements in table to max
    {
        sT[i] = size;
    }

    for(int i = size-1; i>=0; i--)
    {
        m = i, suffixIndex = i; //Current index
        j=0;
        while(m <= size-1) //Building suffix
        {
            suffix[j] = str[m];
            j++;
            m++;
        }
        int k, length, l = 0;
        count = 0; //The number of characters between the suffix and what is found
        for(int i = size-j-1; i>=0; i--) //Starting at first char not in the suffix
        {
            length = 0;
            numRight = 0;
            k=0;
            l=0;
            m = i-(j-1); //Moving back the size of the suffix
            while(m <= i) //Reading all the letters in the suffix in question
            {
                //printf("%d\n", m);
                if(m >= 0)
                {
                    if(str[m] == suffix[l])
                    {
                        numRight++;
                        k++;
                        length++;
                    }
                    else
                    {
                        length++;
                    }       
                }
                m++;
                l++;
            }
            count++;
            if(numRight == length) //numright is equal to suffix length
            {
                //printf("Index: %d is set to %d\n", suffixIndex, count + j - numRight);
                sT[suffixIndex] = count + j - numRight;
                break;
            }
        }
    }
}

/*
*This function uses a Boyer-Moore algorithm to search for a pattern which was
*given by the user, in a 2d array that holds the strings from the file data_5.txt
*/
void bmSearchForPattern(int bST[], int gST[], char str[], char line[44049][100])
{
    int found = 0, count = 0, patternShift = 0, numRight = 0, flag = 0;
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
                flag = 0;
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
                int badValue, goodValue;
                goodValue = gST[m-numRight];
                if(bST[index]-numRight > 0) //If t(c) - k > 0
                    badValue = bST[index]-numRight;
                else //Else shift only one spot
                    badValue = 1;

                if(badValue>=goodValue)
                {
                    j = j + badValue;
                }
                else
                {
                    j = j + goodValue;
                }

            }
        }
    }
    printf("----------------------\n");
    printf("Boyer-Moore Algorithm\n");
    printf("----------------------\n");
    printf("%d occurences of %s\n", found, str);
    printf("Number of pattern shifts: %d\n", patternShift);
}
