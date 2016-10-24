#ifndef GRAPHSHORTESTPATHS_GRAPH_H
#define GRAPHSHORTESTPATHS_GRAPH_H

#include <string>
#include "Index.h"
#include "Buffer.h"
#include "LinkedList.h"

struct NodeArray {
    uint32_t *array;
    uint32_t size;
    NodeArray() : array(NULL), size(0) {}
    ~NodeArray();
    void print();
};

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
    void expand(uint32_t &nodeId, LinkedList<int> frontier);

public:
    Graph() {}
    ~Graph() {}
    void insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId);
    NodeArray *getNeighbors(const uint32_t &nodeId, std::string direction);
    NodeArray *getNeighbors(const uint32_t &nodeId, Index &index, Buffer &buffer);
    void print();
};


#endif //GRAPHSHORTESTPATHS_GRAPH_H
