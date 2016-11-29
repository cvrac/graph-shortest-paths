#ifndef GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
#define GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H

#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "SCC.hpp"
#include "CC.hpp"

class OperationsControl {

public:
    OperationsControl(uint32_t &hashSize);
    ~OperationsControl();
    void run(const uint32_t &hashSize);
    int estimateShortestPath(uint32_t &source, uint32_t &target);

private:
    void buildGraph();
    void runQueries();

    Graph graph_;
    ShortestPath path_;
    SCC strongly_conn_;
    CC connected_components_;
};

#endif //GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
