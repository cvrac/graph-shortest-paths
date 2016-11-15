#ifndef ARRAY_HPP
#define ARRAY_HPP

/*GENERIC ARRAY IMPLEMENTATION
 *Array is used as either a queue or stack fashion.
 */

#include <iostream>
#include <assert.h>
#include <string.h>

template <class T>
class Array {

public:

    Array();
    Array(const char alloc_type, const char use,  const int size, const int factor);
    ~Array();
    bool full();
    int size();
    int maxsize();
    void push(const T& data);
    void push_back(const T& data);
    T &pop_front();
    T &pop_back();
    void clear();

private:

    void reallocatorSts();
    void reallocatorStd();
    void reallocatorQus();
    void reallocatorQud();

    T *array;
    unsigned int size_;
    unsigned int elements_;
    unsigned int head_;
    unsigned int back_;
    char allocator_type_;
    char resize_;
    int resize_factor_;
};

template <class T>
Array<T>::Array() : array(NULL), size_(0), elements_(0), head_(-1), back_(-1),
    allocator_type_('s'), resize_('s'), resize_factor_(4) { }

template <class T>
Array<T>::Array(const char alloc_type, const char use, const int size, const int factor) :
    array(new T[size]), size_(size), elements_(0), head_(0), back_(0),
    allocator_type_(alloc_type), resize_(use), resize_factor_(factor) {

    assert(array != NULL);

}

template <class T>
Array<T>::~Array() {
    if (array != NULL) {
        delete[] array;
        array = NULL;
        size_ = 0;
        elements_ = 0;
        head_ = -1;
        back_ = -1;
    }
}


template <class T>
void Array<T>::reallocatorSts() {
    T *old = array;
    array = new T[size_ << 1];
    memcpy(array, old, size_ * resize_factor_);
    size_ <<= 1;
    delete[] old;
    old = NULL;
}

template <class T>
void Array<T>::reallocatorStd() {
    T *old = array;
    array = new T[size_ << 1];
    memcpy(array, old, size_ * resize_factor_);
    size_ <<= 1;
    delete[] old;
    old = NULL;
}

template <class T>
void Array<T>::reallocatorQus() {
    T *old = array;
    array = new T[size_ << 1];
    memcpy(array, old, size_ * resize_factor_);
    memcpy(array + size_, old, back_ * resize_factor_);
    back_ = size_ + back_;
    size_ <<= 1;
    delete[] old;
    old = NULL;
}

template <class T>
void Array<T>::reallocatorQud() {

}

//checks whether the array is full
template <class T>
bool Array<T>::full() {
    return elements_ == 0;
}

//returns the current number of elements on the array
template <class T>
int Array<T>::size() {
    return elements_;
}

//returns the maximum size of the array
template <class T>
int Array<T>::maxsize() {
    return size_;
}

//inserts an element on the array, stack way
template <class T>
void Array<T>::push(const T& data) {
    if (full()) {
        switch (resize_) {
            case 's':
            reallocatorSts();
            break;
            case 'd':
            reallocatorStd();
            break;
        }
    }
    array[back_] = data;
    ++back_;
    ++elements_;
}

//inserts an element on the array, queue way
template <class T>
void Array<T>::push_back(const T& data) {
    if (full()) {
        switch (resize_) {
            case 's':
            reallocatorQus();
            break;
            case 'd':
            reallocatorQud();
            break;
        }
    }
    array[back_] = data;
    back_ = (back_ + 1) % size_;
    ++elements_;
}


template <class T>
T &Array<T>::pop_front() {
    if (!this->empty()) {
        int temp = head_;
        head_ = (head_ + 1) % size_;
        --elements_;
        return array[temp];
    }
}

template <class T>
T &Array<T>::pop_back() {
    if (!this->empty()) {
        int temp = back_;
        back_ = (back_ + 1) % size_;
        --elements_;
        return array[temp];
    }
}

template <class T>
void Array<T>::clear() {
    head_ = 0;
    back_ = 0;
    elements_ = 0;
}


#endif
