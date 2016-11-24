#include "Garray.hpp"

#include <iostream>

using namespace std;

template <class T>
Garray<T>::Garray() : array_(new T[3]), size_(3), head_(0), tail_(0), elements_(0) {
}

template <class T>
Garray<T>::~Garray() {
    delete[] array_;
}

template <class T>
void Garray<T>::enqueue(const T &element) {
    if (this->full()) {
        T *old_array = array_;
        array_ = new T[size_ * 2];
        memcpy(array_, old_array, size_ * sizeof(T));
        delete[] old_array;
        memcpy(array_ + size_, array_, tail_ * sizeof(T));
        tail_ = size_ + tail_;
        size_ *= 2 ;
    }
    array_[tail_] = element;
    tail_ = (tail_+1) % size_;
    ++elements_;
}

template <class T>
void Garray<T>::print() const {
    cout << "size: " << size_ << ", elements: " << elements_ << ", head: " << head_ << ", tail: " << tail_ << endl;
    if (this->isEmpty()) {
        return;
    }
    int left = elements_;
    for (int cur = head_ ; cur < size_ && left ; cur++, left--) {
        cout << array_[cur] << "\n";
    }
    if (left) {
        for (int cur = 0 ; cur < tail_ ; cur++) {
            cout << array_[cur] << "\n";
        }
    }
    cout << endl;
}