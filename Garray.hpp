#ifndef GRAPHSHORTESTPATHS_GARRAY_H
#define GRAPHSHORTESTPATHS_GARRAY_H

#include "stdint.h"

#include <cstring>
#include <iostream>

/* The array can be initialised with 0 size to avoid memory allocation (no arguments constructor).
 * The value below refers to the size the array will acquire on the first insertion if it was initialised with 0 size. */
#define INITIAL_ARRAY_SIZE 16

template <class T>
class Garray {
public:
    Garray();
    Garray(const uint32_t &size);
    ~Garray();
    void enqueue(const T &element) {this->push(element, 'Q');}
    void enstack(const T &element) {this->push(element, 'S');}
    void increaseSize(const uint32_t &min_size);
    void pushBatch(T *batch, const uint32_t &batchSize);
    T popFront();
    T popBack();
    bool isFull() const {return elements_ == size_;}
    bool isEmpty() const {return !elements_;}
    void clear() {head_ = tail_ = elements_ = 0;}
    uint32_t getSize() const {return size_;}
    uint32_t getHead() const {return head_;}
    uint32_t getTail() const {return tail_;}
    uint32_t getElements() const {return elements_;}
    T &operator[](uint32_t i);
    void print() const;

private:
    void push(const T &element, const char &mode);

    T *array_;
    uint32_t size_;
    uint32_t head_;
    uint32_t tail_;
    uint32_t elements_;
};

template <class T>
Garray<T>::Garray() : array_(NULL), size_(0), head_(0), tail_(0), elements_(0) {}

template <class T>
Garray<T>::Garray(const uint32_t &size) : size_(size), head_(0), tail_(0), elements_(0) {
    if (size) {
        array_ = new T[size];
    } else {
        array_ = NULL;
    }
}

template <class T>
Garray<T>::~Garray() {
    if (array_ != NULL) {
        delete[] array_;
    }
}

template <class T>
void Garray<T>::push(const T &element, const char &mode) {
    if (array_ == NULL) {
        array_ = new T[INITIAL_ARRAY_SIZE];
        size_ = INITIAL_ARRAY_SIZE;
    }
    if (this->isFull()) {
        T *old_array = array_;
        array_ = new T[size_ * 2];
        memcpy(array_, old_array, size_ * sizeof(T));
        delete[] old_array;
        if (mode == 'Q') {
            memcpy(array_ + size_, array_, tail_ * sizeof(T));
        }
        tail_ = size_ + tail_;
        size_ *= 2 ;
    }
    array_[tail_] = element;
    tail_ = (tail_ + 1) % size_;
    elements_++;
}

/* For queue use */
template <class T>
T Garray<T>::popFront() {
    if (! this->isEmpty()) {
        uint32_t temp = head_;
        head_ = (head_+1) % size_;
        --elements_;
        return array_[temp];
    }
}

/* For array/stack use */
template <class T>
T Garray<T>::popBack() {
    if (! this->isEmpty()) {
        --elements_;
        return array_[--tail_];
    }
}

/* For array/stack use */
template <class T>
inline void Garray<T>::increaseSize(const uint32_t &min_size) {
    if (size_ < min_size) {
        size_ = (size_ == 0) ? 1 : size_;
        while (size_ <= min_size) {
            size_ *= 2;
        }
        T *old_array = array_;
        array_ = new T[size_];
        delete[] old_array;
    }
}

/* For array/stack use */
template <class T>
inline void Garray<T>::pushBatch(T *batch, const uint32_t &batchSize) {
    this->increaseSize(batchSize);
    memcpy(&array_[tail_], batch, batchSize * sizeof(T));
    elements_ += batchSize;
    tail_ += batchSize;
}

template <class T>
T &Garray<T>::operator[](uint32_t i) {
    assert(i < this->size_);
    return this->array_[i];
}

template <class T>
void Garray<T>::print() const {
    std::cout << "size: " << size_ << ", elements: " << elements_ << ", head: " << head_ << ", tail: " << tail_ << std::endl;
    if (this->isEmpty()) {
        return;
    }
    uint32_t left = elements_;
    for (uint32_t cur = head_ ; cur < size_ && left ; cur++, left--) {
        std::cout << array_[cur] << "\n";
    }
    if (left) {
        for (uint32_t cur = 0 ; cur < tail_ ; cur++) {
            std::cout << array_[cur] << "\n";
        }
    }
    std::cout << std::endl;
}

#endif //GRAPHSHORTESTPATHS_GARRAY_H
