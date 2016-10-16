#ifndef GRAPHSHORTESTPATHS_GRAPH_H
#define GRAPHSHORTESTPATHS_GRAPH_H

#include "Index.h"
#include "Buffer.h"

class Graph {

private:
    Index outerIndex;
    Buffer outerBuffer;
    Index innerIndex;
    Buffer innerBuffer;

public:
    Graph() {}
    ~Graph() {}
    void insertNode(const int32_t nodeId);
    void insertEdge(const int32_t &sourceNodeId, const int32_t &targetNodeId);
    void print();
};

#endif //GRAPHSHORTESTPATHS_GRAPH_H
