#ifndef GRAPHSHORTESTPATHS_BUFFER_H
#define GRAPHSHORTESTPATHS_BUFFER_H

#include <stdint.h>

#include "ListNode.hpp"

#define INITIAL_MAX_LIST_NODES 10000

struct BufferFeedback {

public:
    BufferFeedback(const bool &edgeExists, const uint32_t &lastPos) : edgeExists(edgeExists),  lastPos(lastPos) {}

    bool edgeExists;
    uint32_t lastPos;
};

class Buffer {

public:
    Buffer();
    ~Buffer();
    ListNodePos allocNewNode();
    ListNode getListNode(const uint32_t &listNodePos) const {return buffer[listNodePos];}
    BufferFeedback insertNeighbor(const uint32_t &firstPos, const uint32_t &neighborId, bool *skipSearch);
    uint32_t getTotalReallocs() const {return totalReallocs;}
    void print() const;

private:
    ListNode *getListNode(const uint32_t &listNodePos) {return &buffer[listNodePos];}

    ListNode *buffer;
    uint32_t curListNodes;
    uint32_t maxListNodes;
    uint32_t totalReallocs;
};

#endif //GRAPHSHORTESTPATHS_BUFFER_H
