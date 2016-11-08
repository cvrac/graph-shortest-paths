#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <cstring>
#include "Queue.hpp"

using namespace std;

Queue::Queue() : size_(8192), head_(0), tail_(0), elements_(0) {
    // queueArray_ = new uint32_t[size_];
    queueArray_ = (uint32_t *) malloc(size_ * sizeof(uint32_t));
}

Queue::~Queue() {
    free(queueArray_);
    queueArray_ = NULL;
}

void Queue::push(uint32_t &id) {
    if (!this->full()) {
        queueArray_[tail_] = id;
        tail_ = (tail_+1) % size_;
        ++elements_;
    } else {
        queueArray_ = (uint32_t *) realloc(queueArray_, size_ << 1 * sizeof(uint32_t));
        memcpy(queueArray_ + size_, queueArray_, tail_ * sizeof(uint32_t));
        tail_ = size_ + tail_;
        size_ <<= 1;
        queueArray_[tail_] = id;
        tail_ = (tail_+1)%size_;
        ++elements_;
    }
}

void Queue::pushBatch(const uint32_t *batch, const uint32_t &batch_size) {
    if (elements_ + batch_size <= size_) {
        uint32_t pushed = 0;
        if (head_ <= tail_) {
            uint32_t right_space = size_ - tail_;
            if (right_space >= batch_size) {
                memcpy(queueArray_ + tail_, batch, batch_size * sizeof(uint32_t));
                pushed += batch_size;
                tail_ += batch_size;
                if (tail_ == size_) {
                    tail_ = 0;
                }
            }
            else {
                memcpy(queueArray_ + tail_, batch, right_space * sizeof(uint32_t));
                pushed += right_space;
                tail_ = 0;
            }
        }
        if (tail_ <= head_ && pushed != batch_size) {
            memcpy(queueArray_ + tail_, batch + pushed, (batch_size - pushed) * sizeof(uint32_t));
            pushed += (batch_size - pushed);
            tail_ += pushed;
        }
    }
    else {
        int new_size = size_;
        while (elements_ + batch_size < new_size) {
            new_size <<= 1;
        }
        queueArray_ = (uint32_t *) realloc(queueArray_, new_size * sizeof(uint32_t));
        if (tail_ <= head_) {
            memcpy(queueArray_ + size_, queueArray_, tail_ * sizeof(uint32_t));
            tail_ = size_ + tail_;
        }
        memcpy(queueArray_ + tail_, batch, batch_size * sizeof(uint32_t));
        size_ = new_size;
    }
    elements_ += batch_size;
}

uint32_t Queue::pop() {
    if (!this->empty()) {
        int temp = head_;
        head_ = (head_+1) % size_;
        --elements_;
        return queueArray_[temp];
    }
}

bool Queue::empty() {
    return (elements_ == 0);
}

bool Queue::full() {
    return (elements_ == size_);
}

void Queue::clear() {
    head_ = 0;
    tail_ = 0;
    elements_ = 0;
}

int Queue::size() {
    return elements_;
}

void Queue::print() {
    for (int i = 0; i < size_; i++)
        cout << queueArray_[i] << " ";
    cout << endl;
}

// main() {
//     uint32_t x;
//     Queue q;
//     x = 2;
//     q.push(x);
//     q.print();
//     x = 3;
//     q.push(x);
//     q.print();
//     x = 4;
//     q.push(x);
//     q.print();
//
//     cout << q.pop() << endl;
//     q.print();
//
//     x = 5;
//     q.push(x);
//     q.print();
//
//     x = 6;
//     q.push(x);
//     q.print();
//
//     x = 7;
//     q.push(x);
//     q.print();
//
//     cout << endl;
//     while (!q.empty())
//         cout << q.pop() << endl;
// }
