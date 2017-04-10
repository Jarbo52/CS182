/*
 * =====================================================================================
 *
 *       Filename:  avl.c
 *
 *    Description:  Implementation of AVL trees
 *
 *        Version:  1.0
 *        Created:  03/31/2017 01:31:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jared Bass
 *         
 *         I pledge my honor that I have abdided by the Stevens Honor System
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "SVdict.h"

void* modifiedLookup(SVdict d, char* key, void* nVal, int updating);

typedef struct node* Node;
struct node
{
    char* key;
    void* val;
    Node left;
    Node right;
    
    int leftBalance;
    int rightBalance;   
    int factor;   
};

struct sv_dict
{
    Node root;
};


void swapChildren(Node n)
{
    Node temp = n->left;
    n->left = n->right;
    n->right = temp;
}

void leftRotate(Node n)
{
    swapChildren(n);

    char* tempK = n->key;
    void* tempV = n->val;
    n->key = n->left->key;
    n->val = n->left->val;
    n->left->key = tempK;
    n->left->val = tempV;
    swapChildren(n->left);
    
    Node temp = n->left->left;
    n->left->left = n->right;
    n->right = temp;
}

void rightRotate(Node n)
{
    swapChildren(n);

    char* tempK = n->key;
    void* tempV = n->val;
    n->key = n->right->key;
    n->val = n->right->val;
    n->right->key = tempK;
    n->right->val = tempV;

    swapChildren(n->right);

    Node temp = n->right->right;
    n->right->right = n->left;
    n->left = temp;
}


void rightLeftRotate(Node n)
{
    rightRotate(n->right);
    leftRotate(n);
}

void leftRightRotate(Node n)
{
    leftRotate(n->left);
    rightRotate(n);
}

// RL on N = R on N-> R then L on N
// LR on N = L on N-> L then R on N

SVdict makeSVdict()
{
    SVdict s = (SVdict) malloc(sizeof(struct sv_dict));
    s->root = NULL;
    return s;
}

void disposeHelp(Node n)
{
    if(n != NULL)
    {
        disposeHelp(n->left);
        disposeHelp(n->right);

        free(n->key);
        n->left = NULL;
        n->right = NULL;
        n->factor = 0;
        n->leftBalance = 0;
        n->rightBalance = 0;
        
        free(n);
        n = NULL;
    }
}

void disposeSVdict(SVdict d)
{
    disposeHelp(d->root);
    free(d);
    return;   
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
    if(strcmp(curr -> key, desiredKey) == 0)
        return 1;

    int keyFound = 0;
    
    //Recursively check down the left side
    keyFound = hasKeyHelper(curr -> left, desiredKey);

    //If it was not found, check the right side
    if(keyFound == 0)
        keyFound = hasKeyHelper(curr -> right, desiredKey);
    
    return keyFound;
}

int hasKey(SVdict d, char* key)
{
    return hasKeyHelper(d->root, key);
}

int max(int a, int b)
{
    return (a>=b?a:b);
}

int height(Node n)
{
    if(n == NULL)
        return -1;
    
    return max(height(n->left), height(n->right)) + 1;
}

void addHelper(Node n, Node add, int prev)
{
    //Node goes to left
    if(strcmp(n->key, add->key) >= 0)
    {
        //Leaf is null can add
        if(n->left == NULL)
        {
            n->left = add;
        }
        else
        {
            //Recurse
            addHelper(n->left, add, 0);
            
            //Update height of left subtree and possibly balance
            n->leftBalance = height(n->left);
            n->rightBalance = height(n->right);
            n->factor = n->leftBalance - n->rightBalance;

            if(n->factor > 1 || n->factor < -1)
            {
                if(n->factor > 1)
                {
                    //Double Left
                    if(strcmp(n->left->key, add->key) >= 0)
                        rightRotate(n);
                    //Left Right      
                    else
                      leftRightRotate(n); 


                    n->leftBalance = height(n->left);
                    n->rightBalance = height(n->right);
                    n->factor = n->leftBalance - n->rightBalance;
                }
                else
                {
                    //Should never occur?
                    //Or matter?
                }
            }
        }
    }
    //Node goes to right    
    else
    {
        if(n->right == NULL)
            n->right = add; 
        else
        {
            addHelper(n->right, add, 1);
            
            n->leftBalance = height(n->left);
            n->rightBalance = height(n->right);

            n->factor = n-> leftBalance - n->rightBalance;

            if(n->factor > 1 || n->factor < -1)
            {
                if(n->factor > 1)
                {
                    
                }
                else
                {
                    if(strcmp(n->right->key, add->key) < 0)
                        leftRotate(n);
                    else
                        rightLeftRotate(n);                   
                    
                    n->leftBalance = height(n->left);
                    n->rightBalance = height(n->right);
                    n->factor = n->leftBalance - n->rightBalance;
                }
            }
        }   
    }

}

void add(SVdict d, char* key, void* val)
{
    Node newNode = (Node) malloc(sizeof(struct node));
    char* newKey = malloc(sizeof(char) * strlen(key));
    strncpy(newKey, key, strlen(key));
    newNode -> key = newKey;
    newNode -> val = val;
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> leftBalance = 0;
    newNode -> rightBalance = 0;
    newNode -> factor = 0;

    if(d -> root == NULL)
    {
        d->root = newNode;
        return;
    }

    addHelper(d->root, newNode, -1);
}

int addOrUpdate(SVdict d, char* key, void* val)
{
    if(hasKey(d,key))
    {
        modifiedLookup(d, key, val, 1);
        return 1;
    }
    else
    {
        add(d,key,val);
        return 0;
    }
}

void* lookup(SVdict d, char* key)
{
    return modifiedLookup(d, key, NULL, 0);
}

void* modifiedLookup(SVdict d, char* key, void* nVal, int updating)
{
    Node curr = d->root;
    while(curr != NULL && strcmp(curr->key,key) != 0)
    {
        if(strcmp(curr->key,key) < 0)
            curr = curr->right;
        else
            curr = curr->left;
    }

    if(updating)
    {
        curr -> val = nVal;
        return NULL;
    }
    else
    {
        if(curr == NULL)
            return NULL;
        else
            return curr -> val;
    }
}

void prePrint(Node n, int depth)
{
    for(int i = 0; i < (depth*INDENT); i++)
        printf(" ");
    if(n == NULL)
    {
        printf(EMPTY_PRINT);
        printf("\n");
    }
    else
    {
        printf("%s",n->key);
        printf("\n");
        prePrint(n->left, depth+1);
        prePrint(n->right, depth+1);
    }
}

void preorderKeys(SVdict d)
{
    prePrint(d->root,0);
}

int remKey(SVdict d, char* key)
{
    printf("This is not the remKey you're looking for.\n");
    assert(0);
}
