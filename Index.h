#ifndef GRAPHSHORTESTPATHS_INDEX_H
#define GRAPHSHORTESTPATHS_INDEX_H

#include <sys/types.h>

#define INITIAL_INDEX_MAX_SIZE 4

class Index {

private:
    u_int32_t *index;
    u_int32_t curSize;
    u_int32_t maxSize;

public:
    Index();
    ~Index();
    void insertNode(const u_int32_t& nodeId);
    u_int32_t getListHead(const u_int32_t& nodeId);
    void print() const;
};

#endif //GRAPHSHORTESTPATHS_INDEX_H
