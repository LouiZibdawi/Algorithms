/*******************************************************
Loui Zibdawi                            A3 - P12.c

0924538                                 Mar. 9th, 2017

CIS 3490                                

********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h> 

typedef struct object
{
    int index;
    char signature[50];
}Object;

void findAnagrams(char str[], Object elements[30000], char array[30000][50]);

void quickSort(char str[], int min, int max);

void sortObjects(Object elements[], int min, int max);

int main()
{
    struct timeb start, end;                          
    double diff, total = 0.00;                                               

    Object elements[30000];
    FILE* fp = fopen("data_4.txt", "r");
    char array[30000][50];
    char str[50];

    //Reading in file to array
    for(int i = 0; i<30000;i++)
    {
        fscanf(fp, "%s", array[i]);

        strcpy(elements[i].signature, array[i]);
        elements[i].index = i;

        quickSort(elements[i].signature, 0, strlen(array[i])-1);
    }

    sortObjects(elements, 0, 29999);
    do
    {
        printf("Enter a string(q to exit): ");
        scanf("%s", str);

        if(strcmp(str, "q") == 0)
            break;

        quickSort(str, 0, strlen(str)-1);

        printf("---------------------------\n");
        printf("Presorted Anagram Algorithm\n");
        printf("---------------------------\n");

        ftime(&start);
        findAnagrams(str, elements, array);
        ftime(&end);

        diff = (int) (1000.0 * (end.time - start.time) 
        + (end.millitm - start.millitm));

        total = total + diff;

        printf("Execution time is: %.2lf Milliseconds\n", diff);
    }while(1==1);

    printf("-----------------------------------------\n");
    printf("TOTAL execution time is: %.2lf Milliseconds\n", total);
    printf("-----------------------------------------\n");

    fclose(fp);
}
/*
* Function that finds the anagrams of a string that was inputed by the user,
* based on a presorted list of strings. The function will print all the anagrams 
* and then print the total amount found
*/
void findAnagrams(char str[], Object elements[30000], char array[30000][50])
{
    int first = 0, numAnagrams = 0;
    int last = 29999;
    int middle = (first+last)/2;
    int index = -1;
 
    while (first <= last) 
    {
        if (atoi(elements[middle].signature) < atoi(str)) //Less than
            first = middle + 1;    
        else if(atoi(elements[middle].signature) > atoi(str)) //Greater than
            last = middle - 1;
        else if(first != middle)
            last = middle;
        else
        {
            index = middle;
            break;
        }
 
        middle = (first + last)/2;
    }

    if(index == -1)
    {
        //printf("Not found\n");
    }
    else
    {
        while(atoi(str) == atoi(elements[index].signature))
        {
            if(strlen(str) == strlen(elements[index].signature))
            {
                printf("%s\n", array[elements[index].index]);
                numAnagrams++;
            }
            
            index++;
        }
    }
    printf("Number of Anagrams of %s: %d\n", str, numAnagrams);
}
//quickSort sorts the str from lowest value character to the highest
void quickSort(char str[], int min, int max) 
{
   int pivot, i, j;
   char temp;

   if( min < max ) 
   {
    // divide and conque
        pivot = min;
        i = min; 
        j = max;
            
        while(i < j)
        {
            while(str[i] <= str[pivot] && i < max)
            {
                i++;
            }
            while(str[j] > str[pivot])
            {
                j--;
            }

            if( i >= j ) 
                break;

            temp = str[i]; 
            str[i] = str[j]; 
            str[j] = temp;
        }
        
        temp = str[pivot]; 
        str[pivot] = str[j]; 
        str[j] = temp;

        quickSort( str, min, j-1);
        quickSort( str, j+1, max);
   } 
}
/*
*sortObjects sorts a list of strings(objects) in this case, from lowest to
*highest.
*/
void sortObjects(Object element[], int min, int max) 
{
   int pivot, i, j;
   Object temp;

   if( min < max ) 
   {
    // divide and conque
        pivot = min;
        i = min; 
        j = max;
            
        while(i < j)
        {   
            while(atoi(element[i].signature) <= atoi(element[pivot].signature) && i < max)
            {
                i++;
            }
            while(atoi(element[j].signature) > atoi(element[pivot].signature))
            {
                j--;
            }

            if( i >= j ) 
                break;

            temp = element[i]; 
            element[i] = element[j]; 
            element[j] = temp;
        }
        
        temp = element[pivot]; 
        element[pivot] = element[j]; 
        element[j] = temp;

        sortObjects( element, min, j-1);
        sortObjects( element, j+1, max);
   } 
}

