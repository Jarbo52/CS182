/*
 * =====================================================================================
 *
 *       Filename:  topocycle.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/06/2017 11:09:14 AM
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
#include "topocycle.h"
#include "dfs.h"

int checkForBackEdge(int a, int b, DFSinfo i);

void topocycle(GraphInfo gi)
{
    Graph g = gi->graph;
    DFSinfo info = DFS(g);
    
    int hasCycle = 0;
    int cycleStart = -1;
    int firstChild = -1;
    int verts = numVerts(g);

    for(int i = 0; (hasCycle == 0) && i < verts; i++)
    {
        int* succ = successors(g,i);
        for(int j = 0; (hasCycle == 0) && succ[j] != -1; j++)
        {
            int a = i;
            int b = succ[j];
            
            if(checkForBackEdge(a,b,info))
            {
                hasCycle = 1;
                cycleStart = a;
                firstChild = b;
            }
        }
    }

    char** names = gi->vertnames;

    if(hasCycle)
    {
        printf("Has a cycle: %s", names[cycleStart]);
        int parentNode = info->parent[cycleStart];
        while(parentNode != firstChild)
        {
            printf(" %s",names[parentNode]);
            parentNode = info->parent[parentNode];
        }
        printf(" %s %s\n", names[firstChild], names[cycleStart]);    
    }
    else
    {
        for(int i = verts - 1; i >= 0; i--)
            printf("%s\n", names[info->finorder[i]]);
    }
}

int checkForBackEdge(int a, int b, DFSinfo info)
{   
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;

    if(info->discover[b] < info->discover[a])
        p1 = 1;
    if(info->discover[a] < info->finish[a])
        p2 = 1;
    if(info->finish[a] < info->finish[b])
        p3 = 1;

    return (p1 && p2 && p3);
}
