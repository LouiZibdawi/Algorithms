/*******************************************************
Loui Zibdawi                            A3 - P11.c

0924538                                 Mar. 9th, 2017

CIS 3490                                

********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h> 

void bruteForceFindAnagrams(char str[50], char array[30000][50]);

int main()
{
    struct timeb start, end;                          
    int diff;                                               

    FILE* fp = fopen("data_4.txt", "r");
    char array[30000][50];
    char str[50];

    //Reading in file to array
    for(int i = 0; i<30000;i++)
        fscanf(fp, "%s", array[i]);

    printf("Enter a string: ");
    scanf("%s", str);

    printf("------------------------------\n");
    printf("Brute Force Anagram Algorithm\n");
    printf("------------------------------\n");

    ftime(&start);
    bruteForceFindAnagrams(str, array);
    ftime(&end);

    diff = (int) (1000.0 * (end.time - start.time) 
        + (end.millitm - start.millitm));

    printf("Execution time is: %d Milliseconds\n", diff);

    fclose(fp);
}
/*
*
* Brute force algorithm to find the anagrams of a string that was inputed by the
* user. The function will print all the anagrams and then print the total amount found
*/

void bruteForceFindAnagrams(char str[50], char array[30000][50])
{
    int flag = 0, numAnagrams = 0;
    char tempStr[50];

    for(int i = 0; i<30000; i++) //All strings in input
    {
        strcpy(tempStr, array[i]);
        if(strlen(tempStr) != strlen(str)) //Not the same length
        {
            flag = 0;
            continue;
        }
        else
        {
            for(int j = 0; j<strlen(str); j++) //All characters in user input
            {
                for(int m = 0; m<strlen(tempStr); m++) //All characters in file str
                {
                    if(str[j] == tempStr[m]) //Found character
                    {
                        tempStr[m] = 'a';
                        flag = 1;
                        break;
                    }
                    else
                        flag = 0;
                }
                if(flag == 0)
                    break;

            }
        }
        if(flag == 0) //Character not found, not an anagram
            continue;
        else
        {
            printf("%s\n", array[i]);
            numAnagrams++;
        }
    }
    printf("Number of Anagrams of %s: %d\n", str, numAnagrams);
}