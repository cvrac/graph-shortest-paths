#ifndef GRAPHSHORTESTPATHS_INDEX_H
#define GRAPHSHORTESTPATHS_INDEX_H

#include <stdint.h>
#include "ListNodePos.h"

#define INITIAL_INDEX_MAX_SIZE 100

struct ListHead {
    ListNodePos pos;
    uint32_t totalNeighbors;
    ListHead() : totalNeighbors(0) {}
};

class Index {

private:
    ListHead *index;
    uint32_t curSize;
    uint32_t maxSize;


public:
    Index();
    ~Index();
    void insertNode(const uint32_t &nodeId);
    ListHead getListHead(const uint32_t &nodeId) const {return index[nodeId];}
    uint32_t getCurSize() {return curSize;}
    void setListHeadPos(const uint32_t &nodeId, const ListNodePos head) {index[nodeId].pos = head;}
    void setListHeadNeighbors(const uint32_t &nodeId, const uint32_t &n) {index[nodeId].totalNeighbors = n;}
    uint32_t getListHeadNeighbors(const uint32_t &nodeId) {return index[nodeId].totalNeighbors;}
    void print() const;
};


#endif //GRAPHSHORTESTPATHS_INDEX_H
