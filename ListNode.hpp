#ifndef GRAPHSHORTESTPATHS_LISTNODE_H
#define GRAPHSHORTESTPATHS_LISTNODE_H

#include <stdint.h>
#include "ListNodePos.hpp"

#define MAX_NEIGHBORS 20
class ListNode {

public:
    ListNode() : curNeighbors(0) {}
    ~ListNode() {}
    void insertNeighbor(const uint32_t &neighborId);
    bool isFull() const {return curNeighbors == MAX_NEIGHBORS;}
    void setNextPos(const ListNodePos &nextPos) {this->nextPos = nextPos;}
    ListNodePos getNextPos() {return nextPos;}
    bool search(const uint32_t &targetId);
    uint32_t *getNeighborArray() {return neighbor;}
    uint32_t getNeighborNumber() {return curNeighbors;}
    void print() const;

private:
    uint32_t curNeighbors;
    uint32_t neighbor[MAX_NEIGHBORS];
    uint32_t edgeProperty[MAX_NEIGHBORS];
    ListNodePos nextPos;
};

#endif //GRAPHSHORTESTPATHS_LISTNODE_H
