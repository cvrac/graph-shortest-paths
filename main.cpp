#include <iostream>
#include <stdint.h>
#include "Graph.h"

/* Nodes are expected to come in ascending order starting from 0. */

int main() {
    Graph g;
    g.insertEdge(0,1);
    g.insertEdge(1,0);
    g.insertEdge(1,1);
    g.insertEdge(2,3);
    g.insertEdge(2,4);
    g.insertEdge(2,5);
    g.insertEdge(2,6);
    g.insertEdge(7,2);
    g.insertEdge(2,1);
    g.insertEdge(3,5);
    g.insertEdge(2,7);
    g.insertEdge(2,0);
    g.insertEdge(4,6);
    g.insertEdge(8,7);
    g.insertEdge(9,7);
    g.insertEdge(9,8);
    g.insertEdge(9,1);
    g.insertEdge(9,2);

    /* Duplicates */
    g.insertEdge(0,1);
    g.insertEdge(1,0);
    g.insertEdge(1,1);
    g.insertEdge(2,3);
    g.insertEdge(2,4);
    g.insertEdge(2,5);
    g.insertEdge(2,6);
    g.insertEdge(7,2);
    g.insertEdge(2,1);
    g.insertEdge(3,5);
    g.insertEdge(2,7);
    g.insertEdge(2,0);
    g.insertEdge(4,6);
    g.insertEdge(8,7);
    g.insertEdge(9,7);
    g.insertEdge(9,8);
    g.insertEdge(9,1);
    g.insertEdge(9,2);

    g.print();

    return 0;
}