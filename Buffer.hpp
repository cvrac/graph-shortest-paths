#ifndef GRAPHSHORTESTPATHS_BUFFER_H
#define GRAPHSHORTESTPATHS_BUFFER_H

#include <stdint.h>

#include "ListNode.hpp"

#define INITIAL_MAX_LIST_NODES 10000

struct BufferFeedback {

public:
    BufferFeedback(const bool &edge_exists, const uint32_t &last_pos) : edge_exists(edge_exists),  last_pos(last_pos) {}

    bool edge_exists;
    uint32_t last_pos;
};

class Buffer {

public:
    Buffer();
    ~Buffer();
    ListNodePos allocNewNode();
    ListNode getListNode(const uint32_t &list_node_pos) const {return buffer_[list_node_pos];}
    BufferFeedback insertNeighbor(const uint32_t &first_pos, const uint32_t &neighbor_id, bool *skip_search);
    uint32_t getTotalReallocs() const {return total_reallocs_;}
    void print() const;

private:
    ListNode *getListNode(const uint32_t &list_node_pos) {return &buffer_[list_node_pos];}

    ListNode *buffer_;
    uint32_t cur_list_nodes_;
    uint32_t max_list_nodes_;
    uint32_t total_reallocs_;
};

#endif //GRAPHSHORTESTPATHS_BUFFER_H
