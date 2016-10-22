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
    void insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId, Index &index, Buffer &buffer);
    void insertNodes(const uint32_t &sourceNodeId, const uint32_t &targetNodeId);
    void insertNode(const uint32_t nodeId);
    void print(Index &index, Buffer &buffer);

public:
    Graph() {}
    ~Graph() {}
    void insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId);
    bool shortestPath(const uint32_t &sourceNodeId, const uint32_t &targetNodeId);
    void print();
};

#endif //GRAPHSHORTESTPATHS_GRAPH_H
