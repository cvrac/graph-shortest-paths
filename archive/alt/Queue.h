#ifndef GRAPHSHORTESTPATHS_QUEUE_H
#define GRAPHSHORTESTPATHS_QUEUE_H

#include <stdint.h>

class Queue {
private:
    uint32_t *queueArray;
    int size_;
    int head;
    int tail;
    int elements;
public:
    Queue();
    ~Queue();
    void clear();
    bool empty();
    bool full();
    uint32_t pop();
    void push(uint32_t &temp);
    void pushBatch(const uint32_t *batch, const uint32_t &batch_size);
    int size();
};

#endif
