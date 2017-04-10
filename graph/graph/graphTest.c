/* Sara Dos Santos
 * Jared Bass
 * graphTest.c
 * 02/23/2017
 * I pledge my honor that I have abided by the Stevens Honor System
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "graph.c"

int main()
{ 
    Graph g1 = makeGraph(5, MATRIX);
    Graph g2 = makeGraph(6, MATRIX);
    Graph g3 = makeGraph(7, LIST);
    Graph g4 = makeGraph(8, LIST);

    Graph g5 = cloneGraph(g1, MATRIX);
    Graph g6 = cloneGraph(g1, LIST);
    Graph g7 = cloneGraph(g3, MATRIX);
    Graph g8 = cloneGraph(g3, LIST);

    printf("Creation and cloning completed\n");

    assert (numVerts(g1) == 5);
    assert (numVerts(g2) == 6);
    assert (numVerts(g3) == 7);
    assert (numVerts(g4) == 8);
    assert (numVerts(g5) == 5);
    assert (numVerts(g6) == 5);
    assert (numVerts(g7) == 7);
    assert (numVerts(g8) == 7);
    
    printf("Vertice checking passed\n");
 
    int a = addEdge(g1, 3, 4, 2.5);
    int b = addEdge(g1, 3, 4, 5);
    int c = addEdge(g6, 2, 3, 4.2);
    int d = addEdge(g2, 6, 7, 2);
    int e = delEdge(g1, 3, 4);
    int f = delEdge(g3, 5, 6);
    int g = addEdge(g2, 2, 3, 9);

    assert (a == 0);
    assert (b == 1);
    assert (c == 0);
    assert (d == 1);
    assert (e == 0);
    assert (f == 1);
    assert (g == 0);
    
    printf("Edge addition and deletion passed\n");

    assert (edge(g6, 2, 3) - 4.2 < 0.0001);
    assert (edge(g2, 2, 3) - 9 < 0.0001);
    assert (edge(g5, 1, 2) ==  INFINITY);
    assert (edge(g6, 5, 7) - -1.0 < 0000.1);

    printf("Edge checking passed\n");

    addEdge(g4, 1, 2, 5);
    addEdge(g4, 1, 4, 6);
    addEdge(g4, 1, 7, 3);

    addEdge(g7, 2, 3, 2.1);
    addEdge(g7, 2, 5, 4);
    addEdge(g7, 2, 1, 8);
    addEdge(g7, 2, 6, 4);

    int* h = successors(g4, 1);
    assert (h[0] == 7);
    assert (h[1] == 4);
    assert (h[2] == 2);

    int* i = successors(g7, 2);
    assert (i[0] == 1); 
    assert (i[1] == 3);
    assert (i[2] == 5);
    assert (i[3] == 6);
    
    printf("Successors passed\n");

    addEdge(g1, 2, 3, 4);
    addEdge(g1, 1, 3, 5);
    addEdge(g1, 3, 3, 2);

    addEdge(g8, 1, 6, 5);
    addEdge(g8, 3, 6, 2);
    addEdge(g8, 4, 6, 3);
    addEdge(g8, 2, 6, 1);

    int* j = predecessors(g1, 3);
    assert (j[0] == 1);
    assert (j[1] == 2);
    assert (j[2] == 3);
    
    int* k = predecessors(g8, 6);
    assert (k[0] == 1);
    assert (k[1] == 2);
    assert (k[2] == 3);
    assert (k[3] == 4);
    
    printf("Predeccesors passed\n");

    disposeGraph(g4);
    disposeGraph(g7);   

    printf("All tests passed\n");
}
