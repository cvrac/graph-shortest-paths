#ifndef GRAPHSHORTESTPATHS_BUFFER_H
#define GRAPHSHORTESTPATHS_BUFFER_H

#include <stdint.h>

#include "ListNode.hh"

struct BufferFeedback {

public:
    BufferFeedback(const bool &edge_exists, const long &last_pos) : edge_exists(edge_exists),  last_pos(last_pos) {}

    bool edge_exists;
    long last_pos;
};

class Buffer {

public:
    Buffer(const uint32_t &list_nodes);
    ~Buffer();
    long allocNewNode();
    ListNode *getListNode(const long &list_node_pos) const {return &buffer_[list_node_pos];}
    bool insertNeighbor(const long &first_pos, const uint32_t &neighbor_id, const char &mode, const uint32_t &edge_version, const bool &skip_search, long *last_pos);
    uint32_t getTotalReallocs() const {return total_reallocs_;}
    long getMaxListNodes() const {return max_list_nodes_;}
    long getCurListNodes() const {return cur_list_nodes_;}
    void print() const;
    void init(const uint32_t &size);

private:
    ListNode *buffer_;
    long cur_list_nodes_;
    long max_list_nodes_;
    uint32_t total_reallocs_;
};

#endif //GRAPHSHORTESTPATHS_BUFFER_H
