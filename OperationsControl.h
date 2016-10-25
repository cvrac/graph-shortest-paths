#ifndef GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
#define GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H

#include "Graph.h"
#include "ShortestPath.h"

class OperationsControl {

private:
    Graph graph;
    ShortestPath *path;
    void buildGraph();
    void runQueries();

public:
    OperationsControl() : path(NULL) {}
    ~OperationsControl() {}
    void run();
};

#endif //GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
