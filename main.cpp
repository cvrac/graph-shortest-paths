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

    /* Outer neighbors */
    std::cout << "\n\nOuter neighbors" << std::endl;

    NodeArray *neighbors = g.getNeighbors(0, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(1, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(2, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(3, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(4, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(5, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(6, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(7, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(8, "outer");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(9, "outer");
    neighbors->print();
    delete neighbors;

    /* Inner neighbors */
    std::cout << "\n\nInner neighbors" << std::endl;

    neighbors = g.getNeighbors(0, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(1, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(2, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(3, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(4, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(5, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(6, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(7, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(8, "inner");
    neighbors->print();
    delete neighbors;

    neighbors = g.getNeighbors(9, "inner");
    neighbors->print();
    delete neighbors;

    return 0;
}