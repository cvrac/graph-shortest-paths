#include "Array.hpp"

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

Array::Array() : queueArray_((uint32_t *) malloc(1024 * sizeof(uint32_t))),
    size_(1024), head_(0), tail_(0), elements_(0) {

}

Array::~Array() {
    free(queueArray_);
    queueArray_ = NULL;
}

/* enqueue an element to the queue, if it's not full
 * if full, resize it, and then enqueue
 */
void Array::enqueue(uint32_t &id) {
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

void Array::push(uint32_t &id) {
    if (!this->full()) {
        queueArray_[tail_] = id;
        tail_ = tail_ + 1;
        ++elements_;
    } else {
        queueArray_ = (uint32_t *) realloc(queueArray_, size_ << 1 * sizeof(uint32_t));
        size_ <<= 1;
        queueArray_[tail_] = id;
        tail_ = tail_ + 1;
        ++elements_;
    }
}

uint32_t Array::pop_back() {
    if (!this->empty()) {
        int temp = tail_;
        --tail_;
        --elements_;
        return queueArray_[temp];
    }
}

/* enqueue a batch of elements to the queue */
void Array::enqueueBatch(const uint32_t *batch, const uint32_t &batch_size) {
    if (elements_ + batch_size <= size_) {
        uint32_t enqueueed = 0;
        if (head_ <= tail_) {
            uint32_t right_space = size_ - tail_;
            if (right_space >= batch_size) {
                memcpy(queueArray_ + tail_, batch, batch_size * sizeof(uint32_t));
                enqueueed += batch_size;
                tail_ += batch_size;
                if (tail_ == size_) {
                    tail_ = 0;
                }
            }
            else {
                memcpy(queueArray_ + tail_, batch, right_space * sizeof(uint32_t));
                enqueueed += right_space;
                tail_ = 0;
            }
        }
        if (tail_ <= head_ && enqueueed != batch_size) {
            memcpy(queueArray_ + tail_, batch + enqueueed, (batch_size - enqueueed) * sizeof(uint32_t));
            enqueueed += (batch_size - enqueueed);
            tail_ += enqueueed;
        }
    }
    else {
        int new_size = size_;
        while (elements_ + batch_size > new_size) {
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

/* if queue isn't empty, then pop its head */
uint32_t Array::pop_front() {
    if (!this->empty()) {
        int temp = head_;
        head_ = (head_+1) % size_;
        --elements_;
        return queueArray_[temp];
    }
}

bool Array::empty() {
    return (elements_ == 0);
}

bool Array::full() {
    return (elements_ == size_);
}

void Array::clear() {
    head_ = 0;
    tail_ = 0;
    elements_ = 0;
}

int Array::size() {
    return elements_;
}

int Array::maxsize() {
    return size_;
}

void Array::print() {
    for (int i = 0; i < size_; i++)
        cout << queueArray_[i] << " ";
    cout << endl;
}
