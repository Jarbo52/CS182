/*
 * Jared Bass
 * CS 182
 * Test for BST
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SIdictBST.c"

int main()
{
    SIdict s1;
    s1 = makeSIdict();
    char hello[] = "Hello";
    addOrUpdate(s1,hello, 1);
    addOrUpdate(s1,"Goodbye",2);
    addOrUpdate(s1,"Ciao",3);
    addOrUpdate(s1,"Bueno",4);
    addOrUpdate(s1,"Shalom",5);
    addOrUpdate(s1,"Hello",2);
    Node curr1 = s1->root;
    printTree(curr1);
    printf("\n");
    printf("%i\n", lookup(s1,"Hello"));
    printf("%i\n", lookup(s1,"Ciao"));
    printf("%i\n", lookup(s1,"Shalom"));
    printf("%i\n", lookup(s1,"Goodbye"));
    printf("%i\n", remKey(s1, "Jared"));
    printf("%i\n", remKey(s1, "Ciao"));
    printTree(curr1);
    printf("\n");
    printf("%i\n", remKey(s1, "Hello"));
    printTree(curr1);
    printf("\n");
    addOrUpdate(s1, "Hello", 3);
    addOrUpdate(s1, "Jared", 100);
    addOrUpdate(s1, "Ciao", 6);
    printTree(curr1);
    return 0;
}
