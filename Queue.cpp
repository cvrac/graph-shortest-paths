#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <cstring>
#include "Queue.h"

using namespace std;

Queue::Queue() : size_(8192), head(0), tail(0), elements(0) {
    // queueArray = new uint32_t[size_];
    queueArray = (uint32_t *) malloc(size_ * sizeof(uint32_t));
}

Queue::~Queue() {
    free(queueArray);
    queueArray = NULL;
}

void Queue::push(uint32_t &id) {
    if (!this->full()) {
        queueArray[tail] = id;
        tail = (tail+1) % size_;
        ++elements;
    } else {
        queueArray = (uint32_t *) realloc(queueArray, 2 * size_ * sizeof(uint32_t));
        memcpy(&queueArray[size_], queueArray, tail * sizeof(uint32_t));
        tail = size_ + tail;
        size_ *= 2;
        queueArray[tail] = id;
        tail = (tail+1)%size_;
        ++elements;
    }
}

void Queue::pushBatch(const uint32_t *batch, const uint32_t &batch_size) {
    if (elements + batch_size <= size_) {
        uint32_t pushed = 0;
        if (head <= tail) {
            uint32_t right_space = size_ - tail;
            if (right_space >= batch_size) {
                memcpy(&queueArray[tail], batch, batch_size * sizeof(uint32_t));
                pushed += batch_size;
                tail += batch_size;
                if (tail == size_) {
                    tail = 0;
                }
            }
            else {
                memcpy(&queueArray[tail], batch, right_space * sizeof(uint32_t));
                pushed += right_space;
                tail = 0;
            }
        }
        if (tail <= head && pushed != batch_size) {
            memcpy(&queueArray[tail], &batch[pushed], (batch_size - pushed) * sizeof(uint32_t));
            pushed += (batch_size - pushed);
            tail += pushed;
        }
    }
    else {
        int new_size = size_;
        while (elements + batch_size < new_size) {
            new_size *= 2;
        }
        queueArray = (uint32_t *) realloc(queueArray, new_size * sizeof(uint32_t));
        if (tail <= head) {
            memcpy(&queueArray[size_], queueArray, tail * sizeof(uint32_t));
            tail = size_ + tail;
        }
        memcpy(&queueArray[tail], batch, batch_size * sizeof(uint32_t));
        size_ = new_size;
    }
    elements += batch_size;
}

uint32_t Queue::pop() {
    if (!this->empty()) {
        int temp = head;
        head = (head+1) % size_;
        --elements;
        return queueArray[temp];
    }
}

bool Queue::empty() {
    return (elements == 0);
}

bool Queue::full() {
    return (elements == size_);
}

void Queue::clear() {
    head = 0;
    tail = 0;
    elements = 0;
}

int Queue::size() {
    return elements;
}
