/*
 * Jared Bass
 * Collaborator: Sara Dos Santos
 * CS 182
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SIdictLL.c"

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
    Node curr1 = s1->first;
    while(curr1 != NULL)
    {
        printf("%s\n",curr1->key);
        curr1 = curr1->next;
    }
    remKey(s1,"Shalom");
    printf("last\n");
    printf("%s\n",s1->last->key);
    printf("%s\n","**************");
    printf("%s\n",s1->first->key);
    printf("%i\n", lookup(s1,hello));
    printf("%i\n",remKey(s1,"Dias"));
    printf("%i\n",remKey(s1,"Hello"));
    printf("%i\n",remKey(s1,"Shalom"));
    printf("%i\n",remKey(s1,"Ciao"));
    printf("%s\n","**************");
    Node curr = s1->first;
    while(curr != NULL)
    {
        printf("%s\n",curr->key);
        curr = curr->next;
    }
    
    return 0;

}
