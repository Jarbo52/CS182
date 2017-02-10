/* Jared Bass
 * Collaborator: Sara Dos Santos
 * CS 182
 * Simple Dictionary Using a Linked List */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "SIdict.h"

typedef struct node* Node;
struct node
{
    char* key;
    int val;
    Node next;   
};

struct si_dict
{
    Node first;
    Node last;   
};

SIdict makeSIdict()
{
    SIdict s = (SIdict) malloc(sizeof(struct si_dict));
    s -> first = NULL;
    s -> last = NULL;
    return s;
}

/*
 * Returns 1 if the given dict has the given key, 0 otherwise
 * Precondition: d and key are non-null
 */
int hasKey(SIdict d, char* key)
{
    //Get pointer to first node
    Node curr = d -> first;
    //Go through whole list
    while(curr != NULL)
    {
        //Get current key and compare it to given key returning if applicable
        char* currKey = curr -> key;
        if(strcmp(key, currKey) == 0)
            return 1;

        //Advance the pointer
        curr = curr -> next;
    }

    //If no match was found, return 0
    return 0;
}

/* map key to val;
 * return 1 if key was already present else 0
 * Precondition: d and key are non-null. */
int addOrUpdate(SIdict d, char* key, int val)
{
    //Create new node with given data
    Node newNode = (Node) malloc(sizeof(struct node));
    char* newKey = malloc(sizeof(char)*strlen(key));
    strcpy(newKey,key);
    newNode -> key = newKey;
    newNode -> val = val;
    newNode -> next = NULL;

    //If the list is null, make the new node the first and last element
    //Return 0, since the key could not have been present
    if(d -> first == NULL)
    {
        d -> first = newNode;
        d -> last = newNode;

        return 0;
    }
    else
    {
        //The dictionary has the key, so look for it and update it
        if(hasKey(d,key) == 1)
        {
            //Search for node
            Node curr = d -> first;
            while(strcmp(curr -> key, key) != 0)
            {
                curr = curr -> next;   
            }

            //Update and return
            curr -> val = val;

            return 1;
        }
        //The key is not in the dictionary, add it to the end and reassign last
        else
        {
            d -> last -> next = newNode;
            d ->  last = newNode;

            return 0;
        }

    }

}

/* Returns the value associated with the given key
 * Precondition: d is non-null and key is present */
int lookup(SIdict d, char* key)
{
    //Scans dictionary for key
    Node curr = d -> first;
    while(strcmp(curr -> key, key) != 0)
    {
        curr = curr -> next;
    }

    //Returns value associated with key
    return curr -> val;   
}

int remKey(SIdict d, char* key)
{
    //If the key is not in the dictionary, return 0
    if(hasKey(d,key) == 0)
    {
        return 0;
    }
    //Oh boy
    else
    {
        //The node to remove is the first node
        if(strcmp(d -> first -> key, key) == 0)
        {
            //Zero the node and free it
            Node temp = d->first;
            d->first=temp->next;
            //If it is also the last node, null the last pointer
            if(strcmp(d->last->key,key) == 0)
            {
                d->last = NULL;
            }
            free(temp->key);
            temp->val=0;
            temp->next = NULL;
            free(temp);
            return 1;
        }
        else
        {
            //The node to remove is the last node
            if(strcmp(d->last->key,key) == 0)
            {
                Node temp = d->last;
                Node curr = d->first;

                //Find the previous node so last can be reassigned
                while(strcmp(curr->next->key,temp->key) != 0)
                {
                    curr = curr -> next;
                }
                curr->next = NULL;
                d->last = curr;
                //Zero the node and free it
                free(temp->key);
                temp->val=0; 
                free(temp);
                return 1;
            }
            //The node to remove is any other node
            else
            {
                //Locate the node before the node to be removed
                Node curr = d->first;
                while(strcmp(curr->next->key,key) != 0)
                {
                    curr = curr->next;
                }

                //Save the node so it can be freed
                Node temp = curr-> next;
               
                //Move the next pointer of the previous node over the node to be removed.
                curr->next = curr->next->next;
               
                //Zero the node and free it
                free(temp->key);
                temp->val = 0;
                temp->next = NULL;
                free(temp);
                return 1;
            }            
        }
    }
}

