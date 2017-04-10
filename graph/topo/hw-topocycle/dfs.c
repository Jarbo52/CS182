/*
 * =====================================================================================
 *
 *       Filename:  dfs.c
 *
 *    Description:  DFS search of a graph
 *
 *        Version:  1.0
 *        Created:  03/05/2017 01:47:26 PM
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
#include "dfs.h"

#define white 0
#define gray 1
#define black 2

void dfsVisit(int vertex, DFSinfo in, Graph g, int* color);

int count = 0;
int orderCounter = 0;

DFSinfo DFS(Graph g)
{
    count = 0;
    orderCounter = 0;

    DFSinfo info = (DFSinfo) malloc(sizeof(struct dfsinfo));
    int verts = numVerts(g);
    info->discover = (int*) malloc(sizeof(int) * (verts+1));
    info->finish = (int*) malloc(sizeof(int) * (verts+1));
    info->parent = (int*) malloc(sizeof(int) * (verts+1));
    info->finorder = (int*) malloc(sizeof(int) * (verts+1));
    info->graph = g;
    int* color = (int*) malloc(sizeof(int) * (verts+1));

    for(int i = 0; i < verts; i++)
    {
        info->discover[i] = 0;
        info->finish[i] = 0;
        info->parent[i] = -1;
        color[i] = white;
    }
    info->discover[verts] = -1;
    info->finish[verts] = -1;
    info->parent[verts] = -1;
    
    for(int i = 0; i < verts; i++)
    {
        if(color[i] == white)
            dfsVisit(i, info, g, color);
    } 

    return info;    
}

void dfsVisit(int vertex, DFSinfo in, Graph g, int* color)
{
    color[vertex] = gray;
    count++;
    in->discover[vertex] = count;
    
    int* succ = successors(g,vertex);
    for(int i = 0; succ[i] != -1; i++)
    {
        if(color[succ[i]] == white)
        {
            in->parent[succ[i]] = vertex;
            dfsVisit(succ[i], in, g, color);
        }
    }
    color[vertex] = black;
    in->finorder[orderCounter] = vertex;
    orderCounter++;
    count++;
    in->finish[vertex] = count;
}
