#ifndef GRAPHSHORTESTPATHS_LISTNODE_H
#define GRAPHSHORTESTPATHS_LISTNODE_H

#include <stdint.h>
#include "ListNodePos.h"

#define MAX_NEIGHBORS 3

class ListNode {

private:
    uint32_t curNeighbors;
    uint32_t neighbor[MAX_NEIGHBORS];
    uint32_t edgeProperty[MAX_NEIGHBORS];
    ListNodePos nextPos;

public:
    ListNode();
    ~ListNode() {}
    void insertNeighbor(const uint32_t &neighborId);
    bool isFull() const {return curNeighbors == MAX_NEIGHBORS;}
    void setNextPos(const ListNodePos &nextPos) {this->nextPos = nextPos;}
    ListNodePos getNextPos() {return nextPos;}
    bool search(const uint32_t &targetId);
    void print() const;
};

#endif //GRAPHSHORTESTPATHS_LISTNODE_H
