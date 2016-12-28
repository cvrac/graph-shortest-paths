#ifndef GRAPHSHORTESTPATHS_GARRAY_H
#define GRAPHSHORTESTPATHS_GARRAY_H

#include "stdint.h"

#include <cstring>
#include <iostream>
#include <assert.h>

/* The array can be initialised with 0 size to avoid memory allocation (no arguments constructor).
 * The value below refers to the size the array will acquire on the first insertion if it was initialised with 0 size. */
#define INITIAL_ARRAY_SIZE 2

template <class T>
class Garray {
public:
    Garray();
    Garray(const uint32_t &size);
    ~Garray();
    void init(const uint32_t &size);
    void shrink(const uint32_t &size);
    void enqueue(const T &element) {this->push(element, 'Q');}
    void enstack(const T &element) {this->push(element, 'S');}
    void increaseSize(const uint32_t &min_size);
    void pushBatch(T *batch, const uint32_t &batchSize);
    T popFront();
    T popBack();
    T &top();
    bool isFull() const {return elements_ == size_;}
    bool isEmpty() const {return !elements_;}
    bool search(const T &element);
    void clear() {head_ = tail_ = elements_ = 0;}
    uint32_t getSize() const {return size_;}
    uint32_t getHead() const {return head_;}
    uint32_t getTail() const {return tail_;}
    uint32_t getElements() const {return elements_;}
    T *getArray() {return array_;}
    void setElements(const uint32_t &elements) {elements_ = elements;}
    T &operator[](uint32_t i);
    Garray(const Garray &garray);
    Garray<T>& operator=(const Garray<T> &garray);
    T *retVal() { return this->array_; }
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
        array_ = new T[size_];
        assert(array_ != NULL);
    } else {
        array_ = NULL;
    }
}

template <class T>
Garray<T>::~Garray() {
    if (array_ != NULL) {
       delete[] array_;
       array_ = NULL;
    }
}

template <class T>
void Garray<T>::push(const T &element, const char &mode) {
    if (array_ == NULL) {
        this->init(INITIAL_ARRAY_SIZE);
    }
    if (this->isFull()) {
        T *old_array = array_;
        array_ = new T[size_ * 2];
        memcpy(array_, old_array, size_ * sizeof(T));
        delete[] old_array;
        if (mode == 'Q') {
            memcpy(array_ + size_, array_, tail_ * sizeof(T));
            tail_ = size_ + tail_;
        }
        size_ *= 2 ;
    }
    array_[tail_] = element;
    if (mode == 'Q')
        tail_ = (tail_ + 1) % size_;
    else
        ++tail_;
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
        // int temp = tail_;
        // --tail_;
        // --elements_;
        // return array_[temp];
    }
}

/*returns the element on the top of the stack*/
template <class T>
T &Garray<T>::top() {
    return this->array_[tail_ - 1];
}


/* For array/stack use. Increase size to at least min_size, copy old elements */
template <class T>
inline void Garray<T>::increaseSize(const uint32_t &min_size) {
    if (size_ < min_size) {
        size_ = (size_ == 0) ? 1 : size_;
        while (size_ <= min_size) {
            size_ *= 2;
        }
        T *old_array = array_;
        array_ = new T[size_];
        memcpy(array_, old_array, elements_ * sizeof(T));
        if (old_array != NULL) {
            delete[] old_array;
        }
    }
}

/* For array/stack use */
template <class T>
inline void Garray<T>::pushBatch(T *batch, const uint32_t &batchSize) {
    this->increaseSize(elements_ + batchSize);
    memcpy(&array_[tail_], batch, batchSize * sizeof(T));
    elements_ += batchSize;
    tail_ += batchSize;
}

/* Init size to an exact value, do not copy previous elements */
template <class T>
void inline Garray<T>::init(const uint32_t &size) {
    if (array_ != NULL) {
        delete[] array_;
        array_ = NULL;
    }
    array_ = new T[size];
    size_ = size;
}

/* Shrink to a lower size, copy old elements up to that size */
template <class T>
void Garray<T>::shrink(const uint32_t &size) {
    if (size_ <= size) {
        return;
    }
    T *old_array = array_;
    uint32_t new_elements = (elements_ <= size ? elements_ : size);
    size_ = new_elements;
    elements_ = new_elements;

    array_ = new T[new_elements];
    for (uint32_t i = 0 ; i < new_elements ; i++) {
        array_[i] = old_array[i];
    }
    if (old_array != NULL) {
        delete[] old_array;
    }
}

/* For array/stack use. Can be easily modified to work for queue as well if needed */
template <class T>
bool Garray<T>::search(const T &element) {
    for (uint32_t n = 0 ; n < elements_ ; n++) {
        if (array_[n] == element) {
            return true;
        }
    }
    return false;
}

template <class T>
T &Garray<T>::operator[](uint32_t i) {
    assert(i < this->size_);
    return this->array_[i];
}

template <class T>
Garray<T>::Garray(const Garray &garray) {
    array_ = new T[garray.size_];
    memcpy(array_, garray.array_, garray.size_ * sizeof(T));
    size_ = garray.size_;
    head_ = garray.head_;
    tail_ = garray.tail_;
    elements_ = garray.elements_;
}

template <class T>
Garray<T>& Garray<T>::operator=(const Garray<T> &garray) {
    array_ = new T[garray.size_];
    memcpy(array_, garray.array_, garray.size_ * sizeof(T));
    size_ = garray.size_;
    head_ = garray.head_;
    tail_ = garray.tail_;
    elements_ = garray.elements_;
    return  *this;
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
