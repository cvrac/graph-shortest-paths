#ifndef GRAPHSHORTESTPATHS_GARRAY_H
#define GRAPHSHORTESTPATHS_GARRAY_H

#include <cstring>
#include <iostream>

#define INITIAL_ARRAY_SIZE 131

template <class T>
class Garray {
public:
    Garray();
    ~Garray();
    void enqueue(const T &element) {this->push(element, 'Q');}
    void enstack(const T &element) {this->push(element, 'S');}
    T popFront();
    T popBack();
    bool isFull() const {return elements_ == size_;}
    bool isEmpty() const {return !elements_;}
    void clear() {head_ = tail_ = elements_ = 0;}
    int getSize() const {return size_;}
    int getHead() const {return head_;}
    int getTail() const {return tail_;}
    int getElements() const {return elements_;}
    T &operator[](int i);
    void print() const;

private:
    void push(const T &element, const char &mode);

    T *array_;
    int size_;
    int head_;
    int tail_;
    int elements_;
};

template <class T>
Garray<T>::Garray() : array_(new T[INITIAL_ARRAY_SIZE]), size_(INITIAL_ARRAY_SIZE), head_(0), tail_(0), elements_(0) {
}

template <class T>
Garray<T>::~Garray() {
    delete[] array_;
}

template <class T>
void Garray<T>::push(const T &element, const char &mode) {
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
        int temp = head_;
        head_ = (head_+1) % size_;
        --elements_;
        return array_[temp];
    }
}

/* For stack use */
template <class T>
T Garray<T>::popBack() {
    if (! this->isEmpty()) {
        --elements_;
        return array_[--tail_];
    }
}

template <class T>
void Garray<T>::print() const {
    std::cout << "size: " << size_ << ", elements: " << elements_ << ", head: " << head_ << ", tail: " << tail_ << std::endl;
    if (this->isEmpty()) {
        return;
    }
    int left = elements_;
    for (int cur = head_ ; cur < size_ && left ; cur++, left--) {
        std::cout << array_[cur] << "\n";
    }
    if (left) {
        for (int cur = 0 ; cur < tail_ ; cur++) {
            std::cout << array_[cur] << "\n";
        }
    }
    std::cout << std::endl;
}

template <class T>
T &Garray<T>::operator[](int i) {
    assert(i < this->size_);
    return this->array_[i];
}

#endif //GRAPHSHORTESTPATHS_GARRAY_H
