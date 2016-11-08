#ifndef GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
#define GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H

#include "Graph.hpp"
#include "ShortestPath.hpp"

class OperationsControl {

private:
    Graph graph;
    ShortestPath path;
    void buildGraph();
    void runQueries();

public:
    OperationsControl(uint32_t &hashSize);
    ~OperationsControl();
    void run(const uint32_t &hashSize);
};

#endif //GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
