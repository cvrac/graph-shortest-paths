#include <iostream>
#include <stdint.h>
#include "Graph.h"
#include "ShortestPath.h"
#include "OperationsControl.h"

using namespace std;

int main(int argc, char **argv) {
    uint32_t hashSize = 70537;
    if (argc > 1) {
        hashSize = (uint32_t ) atol(argv[1]);
    }
    OperationsControl *operationsControl = new OperationsControl(hashSize);
    operationsControl->run(hashSize);
    delete operationsControl;
    return 0;

//     Graph g;
//     g.insertEdge(1, 2);
//     g.insertEdge(2, 3);
//     g.insertEdge(3, 1);
//     g.insertEdge(4, 1);
// //    g.insertEdge(4, 1);
//     g.insertEdge(2, 4);
//     g.print();
//     ShortestPath *path = new ShortestPath(g);
//     uint32_t source = 1, target = 3;
//     cout << "shortest path from " << source << " to " << target << " is "
//                                                                 << path->shortestPath(source, target) << endl;
//     delete path;
//     g.insertEdge(4, 5);
//     path = new ShortestPath(g);
//     source = 1, target = 5;
//     cout << "shortest path from " << source << " to " << target << " is "
//                                                                 << path->shortestPath(source, target) << endl;
//     delete path;
//     path = new ShortestPath(g);
//     source = 5, target = 1;
//     cout << "shortest path from " << source << " to " << target << " is "
//                                                                 << path->shortestPath(source, target) << endl;
//     delete path;

//     g.insertEdge(5, 3);
//     path = new ShortestPath(g);
//     source = 1, target = 3;
//     cout << "shortest path from " << source << " to " << target << " is "
//                                                                 << path->shortestPath(source, target) << endl;
//     delete path;

//     g.insertEdge(3, 4);
//     path = new ShortestPath(g);
//     source = 1, target = 4;
//     cout << "shortest path from " << source << " to " << target << " is "
//                                                                 << path->shortestPath(source, target) << endl;
//     delete path;



  /*  g.insertEdge(0,4);
    g.insertEdge(1,3);
    g.insertEdge(5,5);
    g.insertEdge(5,5);

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
//
//    /* Duplicates */
  /*  g.insertEdge(0,1);
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
    g.insertEdge(9,2); */

    return 0;
}