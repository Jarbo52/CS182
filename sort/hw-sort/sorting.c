/*
 * =====================================================================================
 *
 *       Filename:  sorting.c
 *
 *    Description:  Implementation of various sorting methods.
 *
 *        Version:  1.0
 *        Created:  03/16/2017 01:11:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: Jared Bass
 *         
 *         I pledge my honor that I have abided by the Stevens Honor Sysytem. 
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "sorting.h"

int binSearch(char* a[], char* t, int low, int high);


void insertionsort(char* arr[], int l, int r)
{
    char* temp = NULL;
    for(int i = l; i < r-1; i++)
    {
        int j = i+1;
        temp = arr[j];

        int insertionPoint = binSearch(arr,temp, l, j);

        while(j > insertionPoint && j > 0)
        {
            arr[j] = arr[j-1];
            j--;
        }

        arr[j] = temp;
    }
}

int binSearch(char* a[], char* t, int low, int high)
{
    if(low >= high)
    {
        if(strcmp(t, a[low]) > 0)
        {
            return (low + 1);
        }
        return low;
    }
    
    int middle = (low + high)/2;
    
    if(strcmp(t,a[middle]) == 0)
        return (middle+1);

    if(strcmp(t,a[middle]) > 0)
    {
        return binSearch(a,t,middle+1,high);
    }
    else
    {
        return binSearch(a,t,low,middle-1);
    }
}

int median(char* a, char* b, char* c, int d, int e, int f)
{
    char* larger = strcmp(a,b)>0?a:b;
    char* el = strcmp(larger,c)>0?larger:c;

    char* smaller = strcmp(a,b)<0?a:b;
    char* es = strcmp(smaller,c)<0?smaller:c;


    int isa=0;
    int isb=0;
    int isc=0;
    int ist=0;
    
    if(strcmp(el,a) == 0 || strcmp(es,a) == 0)
        isa=1;
    if(strcmp(el,b) == 0 || strcmp(es,b) == 0)
        isb=2;
    if(strcmp(el,c) == 0 || strcmp(es,c) == 0)
        isc=4;

    ist = isa+isb+isc;
    if(ist == 6)
        return d;
    if(ist == 5)
        return e;
    if(ist == 3)
        return f;
    if(ist==7)
        if(strcmp(a,b) == 0)
            return d;
        else
            if(strcmp(b,c) == 0)
                return e;
    return f;
}

int partition(char* arr[], int l, int r)
{
    int pivot = median(arr[l],arr[r-1],arr[(l+r)/2],l,r-1,(l+r)/2);
    char* temp = NULL;

    int lowerVal = l;
    int higherVal = r-1;

    while(lowerVal <= higherVal)
    {
        while(strcmp(arr[lowerVal],arr[pivot])<0)
            lowerVal++;
        while(strcmp(arr[higherVal],arr[pivot])>0)
            higherVal--;

        if(lowerVal <= higherVal)
        {
            temp = arr[lowerVal];
            arr[lowerVal] = arr[higherVal];
            arr[higherVal] = temp;

            lowerVal++;
            higherVal--;
        }
    }

    return higherVal+1;
}

void quicksorthelper(char* arr[], int l, int r, int plus)
{
    if(l < r-1)
    {
        int pivot = partition(arr,l,r);

        if(plus)
        {
            quicksortPlus(arr,l,pivot);
            quicksortPlus(arr,pivot,r);
        }
        else
        {
            quicksorthelper(arr,l,pivot,0);
            quicksorthelper(arr,pivot,r,0);
        }
    }
    //if plus recursively call plus method else recursively call quicksort
}

void quicksort(char* arr[], int l, int r)
{
    quicksorthelper(arr,l,r,0);
}

void quicksortPlus(char* arr[], int l, int r)
{
    if(r-l <= 10)
    {
        insertionsort(arr,l,r);
    }
    else
    {
        quicksorthelper(arr,l,r,1);
    }
}


void compareSorts(char* arr[], int len)
{
    clock_t begin, end;
    double timeSpent = 0;
    char* copy[len];

    //Insertion
    begin = clock();
    for(int i = 0; i < 20; i++)
    {
        for(int c = 0; c < len; c++)
            copy[c] = arr[c];

        insertionsort(copy,0,len);
    }
    end = clock();
    timeSpent = ((double) (end-begin)) / CLOCKS_PER_SEC;
    printf("Time for 20 insertion sorts: %f\n",timeSpent);
    
    //quick
    begin = clock();
    for(int i = 0; i < 20; i++)
    {
        for(int c = 0; c < len; c++)
            copy[c] = arr[c];

        quicksort(copy,0,len);
    }
    end = clock();
    timeSpent = ((double) (end-begin)) / CLOCKS_PER_SEC;
    printf("Time for 20 quick sorts: %f\n",timeSpent);
   
    //quickplus
    begin = clock();
    for(int i = 0; i < 20; i++)
    {
        for(int c = 0; c < len; c++)
            copy[c] = arr[c];

        quicksortPlus(copy,0,len);
    }
    end = clock();
    timeSpent = ((double) (end-begin)) / CLOCKS_PER_SEC;
    printf("Time for 20 quickPlus sorts: %f\n",timeSpent);
}

