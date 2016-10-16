#ifndef GRAPHSHORTESTPATHS_INDEX_H
#define GRAPHSHORTESTPATHS_INDEX_H

#include <stdint.h>
#include "ListNodePos.h"

#define INITIAL_INDEX_MAX_SIZE 4

class Index {

private:
    ListNodePos *index;
    uint32_t curSize;
    uint32_t maxSize;

public:
    Index();
    ~Index();
    void insertNode(const uint32_t &nodeId);
    ListNodePos getListHead(const uint32_t &nodeId) const {return index[nodeId];}
    uint32_t getCurSize() {return curSize;}
    void setListHead(const uint32_t &nodeId, const ListNodePos &head);
    void print() const;
};

#endif //GRAPHSHORTESTPATHS_INDEX_H
