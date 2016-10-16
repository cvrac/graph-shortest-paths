#ifndef GRAPHSHORTESTPATHS_LISTNODE_H
#define GRAPHSHORTESTPATHS_LISTNODE_H

#include <sys/types.h>

#define NEIGHBORS 3

class ListNode {
private:
    u_int32_t neighbor[NEIGHBORS];
    u_int32_t edgeProperty[NEIGHBORS];
    u_int32_t nextListNode;

public:
    ListNode();
    ~ListNode() {}
};

#endif //GRAPHSHORTESTPATHS_LISTNODE_H
