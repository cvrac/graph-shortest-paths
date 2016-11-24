#ifndef GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
#define GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H

#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "SCC.hpp"

class OperationsControl {

public:
    OperationsControl(uint32_t &hashSize);
    ~OperationsControl();
    void run(const uint32_t &hashSize);

private:
    void buildGraph();
    void runQueries();

    Graph graph;
    ShortestPath path;
    SCC stronglyConn;
};

#endif //GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
