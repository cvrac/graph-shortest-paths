#ifndef GRAPHSHORTESTPATHS_BUFFER_H
#define GRAPHSHORTESTPATHS_BUFFER_H

#include "ListNode.h"
#include <sys/types.h>

#define INITIAL_MAX_LIST_NODES 10

class Buffer {
private:
    ListNode *buffer;
    u_int32_t curListNodes;
    u_int32_t maxListNodes;

public:
    Buffer();
    ~Buffer();
    u_int32_t allocNewNode();
    ListNode *getListNode(const u_int32_t& listNode);
};

#endif //GRAPHSHORTESTPATHS_BUFFER_H
