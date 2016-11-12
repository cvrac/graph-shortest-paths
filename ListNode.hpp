#ifndef GRAPHSHORTESTPATHS_LISTNODE_H
#define GRAPHSHORTESTPATHS_LISTNODE_H

#include <stdint.h>
// #include "ListNodePos.hpp"

// Test value: 3
// Actual value: 20

#define MAX_NEIGHBORS 20
class ListNode {

public:
    ListNode() : cur_neighbors_(0), next_pos_(-1) {}
    ~ListNode() {}
    void insertNeighbor(const uint32_t &neighbor_id);
    bool isFull() const {return cur_neighbors_ == MAX_NEIGHBORS;}
    void setNextPos(const long &next_pos) {next_pos_ = next_pos;}
    long getNextPos() {return next_pos_;}
    bool search(const uint32_t &target_id);
    uint32_t *getNeighborArray() {return neighbor_;}
    uint32_t getNeighborNumber() {return cur_neighbors_;}
    void print() const;

private:
    uint32_t neighbor_[MAX_NEIGHBORS];
    uint32_t cur_neighbors_;
    long next_pos_;
    // uint32_t edge_property_[MAX_NEIGHBORS];
    //ListNodePos next_pos_;
};

#endif //GRAPHSHORTESTPATHS_LISTNODE_H
