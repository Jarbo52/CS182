/* 
 * =====================================================================================
 *
 *       Filename:  SIdictBST.c
 *
 *    Description:  Binary search tree using the SIdict node
 *
 *        Version:  1.0
 *        Created:  02/13/2017 09:06:17 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: Jared Bass
 *          Class: CS 182
 *
 *          I pledge my honor that I have abided by the Stevens Honor System.
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "SIdict.h"

typedef struct node* Node;
struct node
{
    char* key;
    int val;
    Node left;
    Node right;

    //Deletion flag
    int deleted;
};

struct si_dict
{
    Node root;
};

SIdict makeSIdict()
{
    SIdict s = (SIdict) malloc(sizeof(struct si_dict));
    s -> root = NULL;
    return s;
}

/*
 * Helper method for hasKey, using the node as a recursive reference point
 */
int hasKeyHelper(Node curr, char* desiredKey)
{
    //Check if null to as not cause seg fault on recursive call
    //If node is null it cannot contain key
    if(curr == NULL)
        return 0;
    if(strcmp(curr -> key, desiredKey) == 0  && curr->deleted == 0)
        return 1;

    int keyFound = 0;
    
    //Recursively check down the left side
    keyFound = hasKeyHelper(curr -> left, desiredKey);

    //If it was not found, check the right side
    if(keyFound == 0)
        keyFound = hasKeyHelper(curr -> right, desiredKey);
    
    return keyFound;
}

/* 
 * Traverses through tree in VLR  pattern to see if key is present
 * Returns 1 if key is found, 0 if key is not in tree
 */
int hasKey(SIdict d, char* key)
{
    return hasKeyHelper(d->root, key);
}

/* 
 * Adds key to BST or updates it if it was present
 * Returns 0 if key was added and 1 if it was updated
 */
int addOrUpdate(SIdict d, char* key, int val)
{
    //Checks if key is present in tree already
    //If so, it only has to be found and updated and no new memory needs to be allocated
    if(hasKey(d, key))
    {
        Node curr = d->root;
        while(strcmp(curr->key, key) != 0)
        {
            if(strcmp(curr->key, key) < 0)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }

        curr->val = val;

        return 1;
    }
    //Key was not found, so malloc space for it and add it at the appropriate point
    else
    {
        Node newNode = (Node)malloc(sizeof(struct node));
        char* newKey = malloc(sizeof(char) * strlen(key));
        strncpy(newKey, key, strlen(key));
        newNode -> key = newKey;
        newNode -> val = val;
        newNode -> deleted = 0;
        newNode -> left = NULL;
        newNode -> right = NULL;

        //Check if tree is null to make new node root
        if(d->root == NULL)
        {
            d -> root = newNode;
        }
        //Tree is not null, so add the new node
        else
        {
            Node prev = d->root;
            Node curr = (strcmp(d->root->key, key) < 0)? prev->right : prev->left;
            while(curr != NULL)
            {
                prev = curr;
                //Deleted copy of old node is found. Possible edge case??
                if(strcmp(curr->key,key) == 0)
                    curr = curr -> left;
                else
                    curr = (strcmp(curr->key, key) < 0) ? curr->right : curr->left;
            }

            if(strcmp(prev->key, key) > 0)
            {
                prev -> left = newNode;
            }
            else
            {
                prev -> right = newNode;
            }
        }

        return 0;
    }
}

/*
 * Returns value associated with key
 * Assumes d is non-null and key is present
 */
int lookup(SIdict d, char* key)
{
    Node curr = d->root;
    while(strcmp(curr->key, key) != 0 && curr->deleted == 0)
    {
        if(strcmp(curr->key, key) < 0)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }

    return curr->val;
}

int remKey(SIdict d, char* key)
{
    if(hasKey(d,key) == 0)
        return 0;

    Node curr = d->root;
    while(strcmp(curr->key, key) != 0 && curr->deleted == 0)
    {
        if(strcmp(curr->key, key) < 0)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }

    curr->deleted = 1;
    return 1;
}

void printTree(Node curr)
{
    if(curr == NULL)
        return;

    printTree(curr->left);
    if(curr->deleted == 0)
        printf("Key: %s Val: %i\n",curr->key,curr->val);
    printTree(curr->right);
}
