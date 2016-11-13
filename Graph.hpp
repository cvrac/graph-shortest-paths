#ifndef GRAPHSHORTESTPATHS_GRAPH_H
#define GRAPHSHORTESTPATHS_GRAPH_H

#include "NodeIndex.hpp"
#include "Buffer.hpp"
#include "HashTable.hpp"
#include "Array.hpp"

struct NodeArray {
public:
    NodeArray() : array(NULL), size(0), count(0) {}
    ~NodeArray();
    void print();

    uint32_t *array;
    uint32_t size;
    uint32_t count;
};

class Graph {

public:
    Graph() {}
    ~Graph();
    void insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id);
    void getNeighbors(const uint32_t &node_id, const char &direction, Array *neighbors);
    NodeArray &getNeighbors(const uint32_t &node_id, const char &direction);
    uint32_t getNeighborsCount(const uint32_t &source, const char &direction);
    uint32_t getNodes() {return inner_index_.getCurSize();}
    uint32_t getStatistics();
    void printAll();
    void print();

private:
    bool insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, NodeIndex *index, Buffer *buffer, const bool &skip_search);
    void insertNodes(const uint32_t &source_node_id, const uint32_t &target_node_id);
    void insertNode(const uint32_t node_id);
    void toggleDirection(const uint32_t &source_node_id, const uint32_t &target_node_id, const uint32_t **node1, const uint32_t **node2, NodeIndex **index, Buffer **buffer);
    void getNeighbors(const uint32_t &node_id, const NodeIndex &index, const Buffer &buffer, Array *neighbors);
    NodeArray &getNeighbors(const uint32_t &node_id, const NodeIndex &index, const Buffer &buffer);
    void printAll(const NodeIndex &index, const Buffer &buffer);
    void print(const NodeIndex &index, const Buffer &buffer);

    NodeArray node_array_;
    NodeIndex outer_index_;
    Buffer outer_buffer_;
    NodeIndex inner_index_;
    Buffer inner_buffer_;

};


#endif //GRAPHSHORTESTPATHS_GRAPH_H
