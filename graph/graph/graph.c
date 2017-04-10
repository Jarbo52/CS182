/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  Representation of a graph using given interface
 *
 *        Version:  1.0
 *        Created:  02/22/2017 01:14:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jared Bass
 *         Collaborator: Sara Dos Santos
 *              
 *         I pledge my honor that I have abided by the Stevens Honor System.
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "graph.h"

typedef struct node* Node;
struct node
{
    int val;
    float weight;
    Node next;
};

struct graph
{
    int* vertices;
    float** adjMatrix;
    Node* adjLists;
    int type;
};

int arrLen(int* a);

/* Make an empty graph with n vertices, using either adjacency matrix 
   or adjacency lists depending on whether rep==MATRIX or rep==LIST.
   Precondition: n>=1 and rep is MATRIX or LIST.
*/
Graph makeGraph(int n, int rep)
{
    Graph g = (Graph) malloc(sizeof(struct graph));
    int* vert = (int*) malloc(sizeof(int) * (n+1));
    for(int i = 0; i < n; i++)
    {   
//        printf("assigning the value of %i to index %i at memory %i\n",i,i,&vert[i]);
        vert[i] = i;
    }
    vert[n] = -1;
    g-> vertices = vert;

    if(rep == MATRIX)
    {
        //nxn matrix
        float** rows = malloc(sizeof(float*) * (n+1));
        for(int i = 0; i < n; i++)
        {
            float* col = malloc(sizeof(float) * (n+1));
            for(int j = 0; j < n; j++)
            {
                col[j] = INFINITY;
            }
            col[n] = -1;
            rows[i] = col;
        }
        rows[n] = NULL;

        g->adjMatrix = rows;
        g->adjLists = NULL;
        g->type = MATRIX;
    }   
    else
    {
        //Make a starting node for each vertice
        Node* startingNodes = (Node*) malloc(sizeof(Node) * (n+1));
        for(int i = 0; i < n; i++)
        {
            int value = -1;
            Node nextNode = NULL;
            float w = INFINITY;
            Node n = (Node) malloc(sizeof(struct node));
            n-> val = value;
            n-> next = nextNode;
            n->weight = w;
            startingNodes[i] = n;
        }
        startingNodes[n] = NULL;

        g-> adjLists = startingNodes;
        g-> adjMatrix = NULL;
        g->type = LIST;
    } 
}

/* make a copy of g, but using the representation
   specified by rep (which is assumed to be MATRIX or LIST) 
*/
Graph cloneGraph(Graph G, int rep)
{   
    int n = arrLen(G->vertices);

    Graph g = (Graph) malloc(sizeof(struct graph));
    int* vert = (int*) malloc(sizeof(int) * (n+1));
    for(int i = 0; i < n; i++)
        vert[i] = i;
    vert[n] = -1;
    g-> vertices = vert;
    
    if(G->type == rep)
    {
        if(rep == MATRIX)
        {
            float** matrix = malloc(sizeof(float*) * (n+1));
            for(int i = 0; i < n; i++)
            {
                float* col = malloc(sizeof(float) * (n+1));
                for(int j = 0; j < n; j++)
                {
                    col[j] = G->adjMatrix[i][j];
                }
                col[n] = -1;
                matrix[i] = col;
            }
            matrix[n] = NULL;

            g-> adjMatrix = matrix;
            g-> adjLists = NULL;
            g-> type = MATRIX;
            
            return g;
        }
        else
        {
            Node* startingNodes = (Node*) malloc(sizeof(Node) * (n+1));
            
            
            Node* adjNodes = G->adjLists;
            int counter = 0;
            while(adjNodes[counter] != NULL)
            {
                Node n = adjNodes[counter];
                Node prev = NULL;
                Node first = NULL;

                while(n != NULL)
                {
                    if(n->weight != INFINITY)
                    {
                        Node newNode = (Node) malloc(sizeof(struct node));
                        newNode-> val = n->val;
                        newNode->weight = n->weight;
                        newNode-> next = NULL;

                        if(prev == NULL)
                        {
                            prev = n;
                            first = n;
                        }
                        else
                        {
                            prev -> next = n;
                            prev = n;
                        }
                   }

                    n=n->next;
                }

                counter++;
                startingNodes[counter] = first;
            }
            startingNodes[n] = NULL;

            g->adjMatrix = NULL;
            g->adjLists = startingNodes;
            g->type = LIST;
            return g;        
        }
    }

    if(rep == MATRIX)
    {
        Node* adjNodes = G->adjLists;

        float** matrix = malloc(sizeof(float*) * (n+1));
        for(int i = 0; i < n; i++)
        {
            float* col = malloc(sizeof(float) * (n+1));
            for(int j = 0; j < n; j++)
            {
                col[j] = INFINITY;
            }
            col[n] = -1;
            matrix[i] = col;
        }
        matrix[n] = NULL;

        int counter = 0;
        while(adjNodes[counter] != NULL)
        {
            Node n = adjNodes[counter];
            
            while(n != NULL)
            {
                if(n->weight != INFINITY)
                {
                    matrix[counter][n->val] = n-> weight;
                }

                n=n->next;
            }

            counter++;
        }

        g->adjMatrix = matrix;
        g->adjLists = NULL;
        g->type = MATRIX;
        return g;
    } 
    else
    { 
        int length = arrLen(G->vertices);
        float** matrix = G->adjMatrix;

        //Make a starting node for each vertice
        Node* startingNodes = (Node*) malloc(sizeof(Node) * (length+1));

        for(int i = 0; matrix[i] != NULL; i++)
        {
            Node prev = NULL;
            Node first = NULL;

            for(int j = 0; j < length; j++)
            {
                if(matrix[i][j] != INFINITY)
                {
                    Node n = (Node) malloc(sizeof(struct node));
                    n-> val = j;
                    n->weight = matrix[i][j];
                    n-> next = NULL;

                    if(prev == NULL)
                    {
                        prev = n;
                        first = n;
                    }
                    else
                    {
                        prev -> next = n;
                        prev = n;
                    }
                }
            }

            startingNodes[i] = first;
        }
        startingNodes[length]=NULL;

        g->adjLists = startingNodes;
        g->adjMatrix = NULL;
        g->type = LIST;
        return g;
    }
}

/* free the graph object and all its resources.
   Postcondition: g is no longer a valid pointer. 
*/
void disposeGraph(Graph G)
{
    int n = arrLen(G->vertices);
    for(int i = 0; i <= n; i++)
    {
        G->vertices[i] = 0;
    }
    free(G->vertices);

    if(G->type == MATRIX)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j <= n; j++)
            {
                G->adjMatrix[i][j]=0;
            }
            G->adjMatrix[i] = NULL;
            free(G->adjMatrix[i]);
        }
        free(G->adjMatrix);
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            Node n = G->adjLists[i];
            while(n!=NULL)
            {
                n->val = 0;
                n-> weight = 0;
                Node temp = n;
                n=n->next;
                temp->next = NULL;
                free(temp);
            }
        }
        free(G->adjLists);
    }

    G->type = 0;
    free(G);
}

/* add edge from source to target with weight w, and return
   OK, if source and target are valid vertex numbers and
   there was no edge from source to target initially.
   Otherwise, make no change and return ERROR. 
*/
int addEdge(Graph G, int source, int target, float w)
{    
    int n = arrLen(G->vertices);

    if(source >= n || target >= n)
    {
        return ERROR;
    }  
    if(G->type == MATRIX)
    {
        if(G->adjMatrix[source][target] == INFINITY)
        {
            G->adjMatrix[source][target] = w;
            return OK;
        }
        else
        {
            return ERROR;
        }
    }
    else
    {
        Node n = G->adjLists[source];
        while(n != NULL)
        {
            if(n->val == target && n-> weight != INFINITY)
                return ERROR;

            n=n->next;
        }
        Node newNode = (Node) malloc(sizeof(struct node));
        newNode-> val = target;
        newNode-> weight = w;
        newNode-> next = G->adjLists[source];
        G->adjLists[source] = newNode;
        return OK;
    }   
}

/* delete edge from source to target, and return
   OK, if there was an edge from source.
   Otherwise, make no change and return ERROR. 
*/
int delEdge(Graph G, int source, int target)
{
    int n = arrLen(G->vertices);

    if(source >= n || target >= n)
    {
        return ERROR;
    }  
    if(G->type == MATRIX)
    {
        if(G->adjMatrix[source][target] == INFINITY)
            return ERROR;
        else
        {
            G->adjMatrix[source][target] = INFINITY;
            return OK;
        }        
    }
    else
    {
        Node n = G->adjLists[source];
        while(n != NULL)
        {
            if(n->val == target)
            {
                if(n->weight == INFINITY)
                    return ERROR;
                else
                {
                    n->weight = INFINITY;
                    return OK;
                }
            }
            n=n->next;
        }
        return ERROR;        
    }
}

/* return weight of the edge from source to target,
   if there is one; otherwise return INFINITY.
   Return -1.0 if source or target are out of range.
*/
float edge(Graph G, int source, int target)
{
    int n = arrLen(G->vertices);

    if(source >= n || target >= n)
    {
        return -1.0;
    }  
    if(G->type == MATRIX)
    {
        return G->adjMatrix[source][target];
    }
    else
    {
        Node n = G-> adjLists[source];
        while(n!= NULL)
        {
            if(n->val == target)
                return n->weight; 
        }     
        return INFINITY;
    }
}

int numVerts(Graph G)
{
    return arrLen(G->vertices);
}

/* a freshly allocated array with the successor
   vertices of source, if any, followed by an entry with -1
   to indicate end of sequence.
   Precondition: source is in range.
   Ownersip: the caller is responsible for freeing the array.
*/
int* successors(Graph G, int source)
{       
    int counter = 0;
    if(G->type == LIST)
    {
        Node* successorNodes = G->adjLists;
        Node n = successorNodes[source];
        
        while(n!= NULL)
        {
            counter++;
            n=n->next;
        }
        int* succ = (int*) malloc(sizeof(int) * (counter+1));
        counter = 0;
        n=successorNodes[source];

        while(n!=NULL)
        {
            succ[counter] = n->val;
            n=n->next;
            counter++;
        }
        succ[counter] = -1;
        
        return succ;
    }
    else
    {
        float** matrix = G->adjMatrix;
        int length = arrLen(G->vertices);
        for(int j = 0; j < length; j++)
        {
            if(matrix[source][j] != INFINITY)
                counter++;
        }

        int* succ = (int*) malloc(sizeof(int) * (counter +1 ));
        counter = 0;
        for(int j = 0; j < length; j++)
        {
            if(matrix[source][j] != INFINITY)
            {
                succ[counter] = j;
                counter++;
            }
        }
        succ[counter] = -1;
        return succ;
    }
}

/* a freshly allocated array with the predecessor
   vertices of target, if any, followed by an entry with -1
   to indicate end of sequence.
   Precondition: target is in range.
   Ownersip: the caller is responsible for freeing the array.
*/
int* predecessors(Graph G, int target)
{
    if(G-> type == MATRIX)
    {
        int counter = 0;
        float** matrix = G-> adjMatrix;
        int length = arrLen(G-> vertices);

        for(int i = 0; i < length; i++)
        {
            if(matrix[i][target] != INFINITY)
            {
                counter++;
            }
        }

        int* pred = (int*) malloc(sizeof(int) * (counter + 1));
        counter = 0;
        for(int i = 0; i < length; i++)
        {
            if(matrix[i][target] != INFINITY)
            {
                pred[counter] = i;
                counter++;
            }
        }
        pred[counter] = -1;
        return pred;
    }
    else
    {
        int counter = 0;
        Node* lists = G->adjLists;
        int length = arrLen(G->vertices);
        int* temp = (int*) malloc(sizeof(int) * (length + 1));
        for(int i = 0; i < length; i++)
        {
            Node n = lists[i];
            while(n!=NULL)
            {
                if(n-> val == target && n->weight != INFINITY)
                {
                    temp[counter] = i;
                    counter++;
                }

                n=n->next;
            }
        }
        temp[counter] = -1;
        
        int* pred = (int*) malloc(sizeof(int) * (counter + 1));
        counter = 0;

        while(temp[counter] != -1)
        {
            pred[counter] = temp[counter];
            temp[counter] = 0;
            counter++;
        }
        pred[counter] = -1;
        temp[counter] = 0;
        free(temp);
        return pred;
    }
}

int arrLen(int* a)
{
    int len = 0;
    while(a[len] != -1)
        len++;

    return len;
}

