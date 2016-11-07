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
        tail = (tail-1) % size_;
        queueArray = (uint32_t *) realloc(queueArray, 2 * size_ * sizeof(uint32_t));
        memcpy(queueArray + size_, queueArray, tail * sizeof(uint32_t));
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

void Queue::print() {
    for (int i = 0; i < size_; i++)
        cout << queueArray[i] << " ";
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
