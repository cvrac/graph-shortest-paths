#include <iostream>
#include "Graph.h"

int main() {
    Graph g;
    g.insertNode(0);
    g.insertNode(1);
    g.insertNode(2);
    g.insertNode(3);
    g.insertNode(4);
    g.insertNode(5);
    g.insertNode(6);


    g.insertEdge(0, 1);
    g.insertEdge(1, 0);
    g.insertEdge(1,1);
    g.insertEdge(2,3);
    g.insertEdge(2,4);
    g.insertEdge(2,5);
    g.insertEdge(2,6);
    g.insertEdge(7,2);
    g.insertEdge(2,1);
    //g.insertEdge(3,5);
    g.insertEdge(2,7);
    g.insertEdge(2,0);


    g.print();

    return 0;
}