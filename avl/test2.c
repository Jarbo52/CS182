/*
 * =====================================================================================
 *
 *       Filename:  test2.c
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  04/01/2017 12:54:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SVdict.h"

int main()
{
    SVdict d1 = makeSVdict();
    
    addOrUpdate(d1,"m","a");
    addOrUpdate(d1,"l","a");
    addOrUpdate(d1,"k","a");
    addOrUpdate(d1,"j","a");
    addOrUpdate(d1,"i","a");
    addOrUpdate(d1,"h","a");
    addOrUpdate(d1,"g","a");
    addOrUpdate(d1,"f","a");
    addOrUpdate(d1,"e","a");
    addOrUpdate(d1,"d","a");
    addOrUpdate(d1,"c","a");
    addOrUpdate(d1,"b","a");
    addOrUpdate(d1,"a","a");
    
    preorderKeys(d1);

    SVdict d2 = makeSVdict();

    addOrUpdate(d2,"m","a");
    addOrUpdate(d2,"n","a");
    addOrUpdate(d2,"o","a");
    addOrUpdate(d2,"p","a");
    addOrUpdate(d2,"q","a");
    addOrUpdate(d2,"r","a");
    addOrUpdate(d2,"s","a");
    addOrUpdate(d2,"t","a");
    addOrUpdate(d2,"u","a");
    addOrUpdate(d2,"v","a");
    addOrUpdate(d2,"w","a");
    addOrUpdate(d2,"x","a");
    addOrUpdate(d2,"y","a");
    addOrUpdate(d2,"z","a");

    printf("\n*****\n");
    preorderKeys(d2);
    printf("\n*****\n");

    SVdict d3 = makeSVdict();

    addOrUpdate(d3, "jared", "a");
    addOrUpdate(d3, "justin", "a");
    addOrUpdate(d3, "chris", "a");
    addOrUpdate(d3, "isaac", "a");
    addOrUpdate(d3, "noah", "a");
    addOrUpdate(d3, "elena", "a");
    addOrUpdate(d3, "sara", "a");
    addOrUpdate(d3, "ed", "a");
    addOrUpdate(d3, "naumann", "a");
    addOrUpdate(d3, "dave", "a");
    addOrUpdate(d3, "potato", "a");
    addOrUpdate(d3, "carrott", "a");
    addOrUpdate(d3, "late", "a");
    addOrUpdate(d3, "a", "a");
    addOrUpdate(d3, "aa", "a");

    preorderKeys(d3);
}
