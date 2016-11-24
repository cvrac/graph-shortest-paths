#ifndef GRAPHSHORTESTPATHS_ARRAY_H
#define GRAPHSHORTESTPATHS_ARRAY_H

#include <stdint.h>

class Array {

public:
    Array();
    ~Array();
    void clear();
    bool empty();
    inline bool full();
    uint32_t pop_back();
    uint32_t pop_front();
    void enqueue(uint32_t &temp);
    void push(uint32_t &temp);
    void enqueueBatch(const uint32_t *batch, const uint32_t &batch_size);
    inline int size();
    inline int maxsize();
    void print();

private:
    uint32_t *queueArray_;
    int size_;
    int head_;
    int tail_;
    int elements_;
};

#endif
