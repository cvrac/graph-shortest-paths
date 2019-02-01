#ifndef GRAPHSHORTESTPATHS_HASHTABLE_H
#define GRAPHSHORTESTPATHS_HASHTABLE_H

#include <iostream>

#include <cstdlib>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "Garray.hh"

template <class T>
class HashTable {

public:
	HashTable(const uint32_t &numofbucks) : hashentries_(numofbucks), table_(hashentries_) {}
	~HashTable() {};
	void insert(const T &nodeid);
	bool search(const T &entry_id);
    bool searchInsert(const T &entry_id);
	void print();
	void clear();
    uint32_t hash(const T &id) {return id % hashentries_;}
    uint32_t getBucketCount(const T &pos) {return table_[hash(pos)].getElements();}

private:
	uint32_t hashentries_;
	Garray<Garray<T> > table_;
};

using namespace std;

template <class T>
void HashTable<T>::clear() {
	for (unsigned int i = 0; i < hashentries_; i++) {
		if (! table_[i].isEmpty()) {
			table_[i].clear();
		}
	}
}

template <class T>
void HashTable<T>::insert(const T &node_id) {
	int pos = this->hash(node_id);
	table_[pos].enstack(node_id);
}

template <class T>
bool HashTable<T>::search(const T& entry_id) {
	int pos = this->hash(entry_id);
	Garray<uint32_t> *temp = &table_[pos];

	for (int i = 0; i < temp->getElements(); i++) {
		if (entry_id == (*temp)[i])
			return true;
	}
	return false;
}

template <class T>
bool HashTable<T>::searchInsert(const T &entry_id) {
    int pos = this->hash(entry_id);
    Garray<uint32_t> *temp = &table_[pos];
    for (int i = 0; i < temp->getElements(); i++) {
        if (entry_id == (*temp)[i])
            return false;
    }
	temp->enstack(entry_id);
    return true;
}

template <class T>
void HashTable<T>::print() {
	Garray<uint32_t> *temp;
	for (unsigned int i = 0; i < hashentries_; i++) {
		cout << "bucket[" << i << "]:" << endl;
		temp = &table_[i];
		for (int i = 0; i < temp->getElements(); i++)
			cout << (*temp)[i] << endl;
	}
}

#endif
