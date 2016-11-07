#ifndef GRAPHSHORTESTPATHS_INDEX_H
#define GRAPHSHORTESTPATHS_INDEX_H

#include <stdint.h>

#include "ListNodePos.h"

#define INITIAL_INDEX_MAX_SIZE 1000

struct ListHead {
    ListHead() : totalNeighbors(0) {}

    ListNodePos pos;
    uint32_t lastPos;
    uint32_t totalNeighbors;};

class Index {

public:
    Index();
    ~Index();
    void insertNode(const uint32_t &nodeId);
    ListHead getListHead(const uint32_t &nodeId) const {return index[nodeId];}
    uint32_t getCurSize() const {return curSize;}
    void setListHeadPos(const uint32_t &nodeId, const ListNodePos &head) {index[nodeId].pos = head;}
    void setListHeadLast(const uint32_t &nodeId, const uint32_t &last) {index[nodeId].lastPos = last;}
    void setListHeadNeighbors(const uint32_t &nodeId, const uint32_t &n) {index[nodeId].totalNeighbors = n;}
    uint32_t getListHeadNeighbors(const uint32_t &nodeId) {return index[nodeId].totalNeighbors;}
    uint32_t getAverageNeighbors();
    uint32_t getTotalReallocs() const {return totalReallocs;}
    void print() const;

private:
    ListHead *index;
    uint32_t curSize;
    uint32_t maxSize;
    uint32_t totalReallocs;
};


#endif //GRAPHSHORTESTPATHS_INDEX_H
