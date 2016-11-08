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
    void insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id);
    void getNeighbors(const uint32_t &node_id, const char &direction, Queue *neighbors);
    NodeArray *getNeighbors(const uint32_t &node_id, const char &direction);
    uint32_t getNodes() {return inner_index_.getCurSize();}
    uint32_t getStatistics();
    void printAll();
    void print();

private:
    bool insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, Index *index, Buffer *buffer, const bool &skip_search);
    void insertNodes(const uint32_t &source_node_id, const uint32_t &target_node_id);
    void insertNode(const uint32_t node_id);
    void toggleDirection(const uint32_t &source_node_id, const uint32_t &target_node_id, const uint32_t **node1, const uint32_t **node2, Index **index, Buffer **buffer);
    void getNeighbors(const uint32_t &node_id, const Index &index, const Buffer &buffer, Queue *neighbors);
    NodeArray *getNeighbors(const uint32_t &node_id, const Index &index, const Buffer &buffer);
    void printAll(const Index &index, const Buffer &buffer);
    void print(const Index &index, const Buffer &buffer);

    Index outer_index_;
    Buffer outer_buffer_;
    Index inner_index_;
    Buffer inner_buffer_;
};


#endif //GRAPHSHORTESTPATHS_GRAPH_H
