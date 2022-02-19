#include <iostream>
#define VISITED true
#define UNVISITED false
#define INFINITY 1  //aqui n sei qual é o valor desta diretriz, mas coloquei 1
                    //porque em outro momento do código é dita como 0

#ifndef DIJSKTRA_H
#define DIJSKTRA_H


int minVertex(Graph* G, int* D) { // Find min cost vertex
    int i, v = -1;
    // Initialize v to some unvisited vertex
    for (i=0; i<G->n(); i++)
        if (G->getMark(i) == UNVISITED) { v = i; break; }
    for (i++; i<G->n(); i++) // Now find smallest D value
        if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
            v = i;
    return v;
}

// Compute shortest path distances from "s".
// Return these distances in "D".
void Dijkstra(Graph* G, int* D, int s) {
    int i, v, w;
    for (int i=0; i<G->n(); i++)
        // Initialize
        D[i] = INFINITY;
    D[0] = 0;
    for (i=0; i<G->n(); i++) {
        // Process the vertices
        v = minVertex(G, D);
        if (D[v] == INFINITY) return; // Unreachable vertices
        G->setMark(v, VISITED);
        for (w=G->first(v); w<G->n(); w = G->next(v,w))
            if (D[w] > (D[v] + G->weight(v, w)))
            D[w] = D[v] + G->weight(v, w);
    }
}

#endif