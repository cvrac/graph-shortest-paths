#ifndef GRAPHSHORTESTPATHS_GRAPH_H
#define GRAPHSHORTESTPATHS_GRAPH_H

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
    bool insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId, Index &index, Buffer &buffer, bool &skipSearch);
    void insertNodes(const uint32_t &sourceNodeId, const uint32_t &targetNodeId);
    void insertNode(const uint32_t nodeId);
    void toggleDirection(const uint32_t &sourceNodeId, const uint32_t &targetNodeId, const uint32_t *&node1, const uint32_t *&node2, Index *&index, Buffer *&buffer);
    void printAll(Index &index, Buffer &buffer);
    void print(Index &index, Buffer &buffer);
    void expand(uint32_t &nodeId, LinkedList<int> frontier);

public:
    Graph() {}
    ~Graph() {}
    void insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId);
    NodeArray *getNeighbors(const uint32_t &nodeId, char &direction);
    NodeArray *getNeighbors(const uint32_t &nodeId, Index &index, Buffer &buffer);
    uint32_t getNodes() {return innerIndex.getCurSize();}
    uint32_t getStatistics();
    void printAll();
    void print();
};


#endif //GRAPHSHORTESTPATHS_GRAPH_H
