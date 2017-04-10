/*
 * =====================================================================================
 *
 *       Filename:  tclose.c
 *
 *    Description:  Implementation of transitive closure of a graph 
 *
 *        Version:  1.0
 *        Created:  04/06/2017 07:19:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jared Bass
 *                  
 *         I pledge my honor that I have abided by the Stevens Honor System.
 *
 * =====================================================================================
 */
#include "tclose.h"

Graph transClose(Graph g)
{
    Graph trans = cloneGraph(g, MATRIX);
    int num = numVerts(trans);

    for(int k = 0; k < num; k++)
    {
        for(int i = 0; i < num; i++)
        {
            for(int j = 0; j < num; j++)
            {
                float proper = edge(trans, i, j) == INFINITY ? INFINITY: 0;
                float fakeA = edge(trans, i, k)== INFINITY? INFINITY : 0;
                float fakeB = edge(trans, k, j) == INFINITY? INFINITY: 0;
                float fake = (fakeA == INFINITY || fakeB == INFINITY) ? INFINITY : 0;
                float newEdge = ((fake != INFINITY) || (proper != INFINITY)) ? 0:INFINITY;
                
                delEdge(trans, i, j);
                if(newEdge != INFINITY)
                    addEdge(trans, i, j, newEdge); 
            }
        }
    }
    return trans;
}
