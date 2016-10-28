#ifndef GRAPHSHORTESTPATHS_BUFFER_H
#define GRAPHSHORTESTPATHS_BUFFER_H

#include "ListNode.h"
#include <stdint.h>

#define INITIAL_MAX_LIST_NODES 1000

struct BufferFeedback {
    bool edgeExists;
    uint32_t lastPos;
    BufferFeedback(const bool &edgeExists, const uint32_t &lastPos) : edgeExists(edgeExists),  lastPos(lastPos) {}
};

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
    BufferFeedback insertNeighbor(const uint32_t &firstPos, const uint32_t &neighborId, bool &skipSearch);
    void print() const;
};

#endif //GRAPHSHORTESTPATHS_BUFFER_H
