#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include "Queue.h"

using namespace std;

Queue::Queue() : size_(16384), head(0), tail(0), elements(0) {
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
        int temp = head;
        int i = 0;
        while (true) {
            if (i >= head)
                break;
            queueArray[i] = queueArray[temp];
            temp++;
            i++;
        }
        tail = i;
        head = i;
        size_ *= 2;
        queueArray[tail] = id;
        tail = (tail+1)%size_;
        ++elements;
    }
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
