/*
 * =====================================================================================
 *
 *       Filename:  dfstest.c
 *
 *    Description:  Test for DFS
 *
 *        Version:  1.0
 *        Created:  03/06/2017 11:18:40 AM
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
#include "graphio.h"
#include "topocycle.h"

int main()
{
    GraphInfo gi1 = readGraph("prereqs.txt", MATRIX);
    Graph g1 = gi1->graph;
    DFSinfo info1 = DFS(g1); 
    int* finOrder = info1->finorder;
    for(int i = 0; i < numVerts(g1); i++)
        printf("%i ", finOrder[i]);
    printf("\n");
    topocycle(gi1);
    return 0;
}
