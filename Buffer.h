#ifndef GRAPHSHORTESTPATHS_BUFFER_H
#define GRAPHSHORTESTPATHS_BUFFER_H

#include "ListNode.h"
#include <stdint.h>

#define INITIAL_MAX_LIST_NODES 100

class Buffer {
private:
    ListNode *buffer;
    uint32_t curListNodes;
    uint32_t maxListNodes;

public:
    Buffer();
    ~Buffer();
    ListNodePos allocNewNode();
    ListNode *getListNode(const uint32_t &listNodePos);
    bool insertNeighbor(const uint32_t &firstPos, const uint32_t &neighborId);
    void print() const;
};

#endif //GRAPHSHORTESTPATHS_BUFFER_H
