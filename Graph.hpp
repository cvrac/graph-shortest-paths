#ifndef GRAPHSHORTESTPATHS_GRAPH_H
#define GRAPHSHORTESTPATHS_GRAPH_H

#include "Index.hpp"
#include "Buffer.hpp"
#include "Queue.hpp"

struct NodeArray {
public:
    NodeArray() : array(NULL), size(0) {}
    ~NodeArray();
    void print();

    uint32_t *array;
    uint32_t size;
};

class Graph {

public:
    Graph() {}
    ~Graph() {}
    void insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId);
    void getNeighbors(const uint32_t &nodeId, const char &direction, Queue *neighbors);
    NodeArray *getNeighbors(const uint32_t &nodeId, const char &direction);
    uint32_t getNodes() {return innerIndex.getCurSize();}
    uint32_t getStatistics();
    void printAll();
    void print();

private:
    bool insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId, Index *index, Buffer *buffer, bool *skipSearch);
    void insertNodes(const uint32_t &sourceNodeId, const uint32_t &targetNodeId);
    void insertNode(const uint32_t nodeId);
    void toggleDirection(const uint32_t &sourceNodeId, const uint32_t &targetNodeId, const uint32_t **node1, const uint32_t **node2, Index **index, Buffer **buffer);
    void getNeighbors(const uint32_t &nodeId, const Index &index, const Buffer &buffer, Queue *neighbors);
    NodeArray *getNeighbors(const uint32_t &nodeId, const Index &index, const Buffer &buffer);
    void printAll(const Index &index, const Buffer &buffer);
    void print(const Index &index, const Buffer &buffer);

    Index outerIndex;
    Buffer outerBuffer;
    Index innerIndex;
    Buffer innerBuffer;
};


#endif //GRAPHSHORTESTPATHS_GRAPH_H
