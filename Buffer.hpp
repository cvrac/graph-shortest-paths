#ifndef GRAPHSHORTESTPATHS_BUFFER_H
#define GRAPHSHORTESTPATHS_BUFFER_H

#include <stdint.h>

#include "ListNode.hpp"

// Test value: 1
// Actual value: 10000

#define INITIAL_MAX_LIST_NODES 20000

struct BufferFeedback {

public:
    BufferFeedback(const bool &edge_exists, const long &last_pos) : edge_exists(edge_exists),  last_pos(last_pos) {}

    bool edge_exists;
    long last_pos;
};

class Buffer {

public:
    Buffer();
    ~Buffer();
    long allocNewNode();
    ListNode *getListNode(const long &list_node_pos) const {return &buffer_[list_node_pos];}
    long insertNeighbor(const long &first_pos, const uint32_t &neighbor_id, const bool &skip_search);
    uint32_t getTotalReallocs() const {return total_reallocs_;}
    long getMaxListNodes() const {return max_list_nodes_;}
    long getCurListNodes() const {return cur_list_nodes_;}
    void print() const;

private:
    //ListNode *getListNode(const long &list_node_pos) {return &buffer_[list_node_pos];}

    ListNode *buffer_;
    long cur_list_nodes_;
    long max_list_nodes_;
    uint32_t total_reallocs_;
};

#endif //GRAPHSHORTESTPATHS_BUFFER_H
