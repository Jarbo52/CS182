/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2017 06:48:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SIdictBST.c"

int main()
{
    SIdict d = makeSIdict();
    addOrUpdate(d, "c", 1);
    addOrUpdate(d, "b", 2);
    addOrUpdate(d, "a", 3);

    printTreePre(d->root);

    rightRotate(d->root);
    
    printf("****************************\n");

    printTreePre(d->root);
    
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    SIdict d2 = makeSIdict();
    addOrUpdate(d2,"a",1);
    addOrUpdate(d2,"b",2);
    addOrUpdate(d2,"c",3);

    printTreePre(d2->root);

    printf("*********************************\n");

    leftRotate(d2->root);

    printTreePre(d2->root);

    printf("***************\n**********************\n");
    
    SIdict d3 = makeSIdict();
    addOrUpdate(d3,"d",4);
    addOrUpdate(d3,"c",40);
    addOrUpdate(d3,"o",6);
    addOrUpdate(d3,"q",7);
    addOrUpdate(d3,"l",5);
    addOrUpdate(d3,"m",50);

    printTreePre(d3->root);

    printf("*************\n");

    rightLeftRotate(d3->root);

    printTreePre(d3->root);
}
