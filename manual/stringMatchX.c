/*
 * =====================================================================================
 *
 *       Filename:  stringMatchX.c
 *
 *    Description:  Checks if a substring occurs in a given string
 *
 *        Version:  1.0
 *        Created:  02/18/2017 01:04:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jared Bass
 *
 *         I pledge my honor that I have abided by the Stevens Honor System.
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int match(char* text, char* pattern)
{
    int textLen = strlen(text);
    int patLen = strlen(pattern);

    //If pattern is longer it cannot appear in text
    if(patLen > textLen)
        return -1;

    for(int i = 0; i < textLen; i++)
    {
        //If we've gone too far and pattern can no longer fit, dont't check
        if(patLen + i <= textLen)
        {
            int valid = 1;
            for(int j = 0; j < patLen; j++)
            {
                //Check equality character by character. If a pair is found that do not match, switch the validity flag to 0
                if(pattern[j] != text[i+j])
                {
                    valid = 0;
                }   
            }

            //If the validity flag remained 1 throughout the whole pattern length, a match was found so return it
            if(valid)
            {
                return i;
            }
        }
    }

    return -1;
}

int main()
{
    assert(match("found", "found") == 0);
    assert(match("found", "lost") == -1);
    assert(match("found", "fount") == -1); 
    assert(match("unfound", "found") == 2);
    assert(match("found", "") == 0);
    assert(match("there is more to life than its speed", "Ghandi") == -1);
    assert(match("nobody noticed him", "not") == 7);

    printf("tests successful\n");
}

/*  Exercise: 
 *
 * Implement the function below, using loop(s) and a brute force algorithm.
 *      Done above.
 *
 * Briefly discuss the time complexity of your implementation:
 *      If the length of the pattern is n, and the length of the text is m, this runs in approximately O(nm) time.
 *
 * What is a good choice of basic operation to count
 *      A good basic operation to count would be checking the equality of two characters
 *
 * What is a good measure of the input size
 *      A good measure of input size is the length of the strings
 *
 * Do some inputs take more time than others?
 *      On average no, no inputs take significantly longer than others. The length of the text is the only factor
 *
 * If so, what inputs are worst case?
 *      Worst case would be a long text and a short pattern. Ex. Pattern = "aaaaaab" Text = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
 *
 * What is the (worst case) time complexity?
 *      The worst case time complexity is the same as the average case, O(nm).
 *
 */
