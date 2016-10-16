#ifndef GRAPHSHORTESTPATHS_BUFFER_H
#define GRAPHSHORTESTPATHS_BUFFER_H

#include "ListNode.h"
#include <stdint.h>

#define INITIAL_MAX_LIST_NODES 10

class Buffer {
private:
    ListNode *buffer;
    uint32_t curListNodes;
    uint32_t maxListNodes;

public:
    Buffer();
    ~Buffer();
    uint32_t allocNewNode();
    ListNode *getListNode(const uint32_t &listNodePos);
    void insertNeighbor(const uint32_t &listNodePos, const uint32_t &neighborId);
    void print() const;
};

#endif //GRAPHSHORTESTPATHS_BUFFER_H
