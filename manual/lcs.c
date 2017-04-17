/*
 * =====================================================================================
 *
 *       Filename:  lcs.c
 *
 *    Description:  Find longest common subsequence in a string 
 *
 *        Version:  1.0
 *        Created:  04/10/2017 09:35:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jared Bass
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max(int x, int y)
{
    return (x>=y)?x:y;
}

int lcs(char* a, char* b, int i, int j)
{
    if(i == 0 || j== 0)
        return 0;

    if(a[i-1] == b[j-1])
        return 1 + lcs(a,b,i-1,j-1);
    else
        return max(lcs(a,b,i-1,j),lcs(a,b,i,j-1));
}

int lcsDyn(char* a, char* b, int i, int j, int** arr)
{

}

int main()
{
    printf("lcs of %s and %s is %i\n","spam","sam!",lcs("spam","sam!", strlen("spam"),strlen("sam!")));
}
