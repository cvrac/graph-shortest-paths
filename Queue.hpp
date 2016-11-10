#ifndef GRAPHSHORTESTPATHS_QUEUE_H
#define GRAPHSHORTESTPATHS_QUEUE_H

#include <stdint.h>

class Queue {

public:
    Queue();
    ~Queue();
    void clear();
    bool empty();
    inline bool full();
    uint32_t pop();
    void push(uint32_t &temp);
    void pushBatch(const uint32_t *batch, const uint32_t &batch_size);
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
