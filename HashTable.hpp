#ifndef GRAPHSHORTESTPATHS_HASHTABLE_H
#define GRAPHSHORTESTPATHS_HASHTABLE_H

#include <iostream>

#include <cstdlib>
#include <string>
#include <stdint.h>
#include <assert.h>

#include "Garray.hpp"

template <class T>
class HashTable {

public:
	HashTable(const uint32_t &numofbucks);
	HashTable() : hashentries_(23), elements_(0), table_(NULL) {}
	~HashTable();
	inline uint32_t size();
	void insert(const T &nodeid);
	bool search(const T &entry_id);
    bool searchInsert(const T &entry_id);
	void print();
	void clear();
    uint32_t hash(const T &id) {return id % hashentries_;}
    uint32_t getBucketCount(const T &pos) {return table_[hash(pos)].count;}

private:
	struct Bucket {
		Bucket();
		~Bucket();

		T *entries;
		uint32_t count;
		uint32_t size;
	};

	uint32_t hashentries_;
	uint32_t elements_;
	Bucket *table_;
};

using namespace std;

template <class T>
HashTable<T>::Bucket::Bucket() : entries(new T[16]), count(0), size(16) {

	assert(entries != NULL);

}

template <class T>
HashTable<T>::Bucket::~Bucket() {

	delete[] entries;
	entries = NULL;

}

template <class T>
HashTable<T>::HashTable(const uint32_t& numofbucks) : hashentries_(numofbucks), elements_(0),
	table_(new Bucket[hashentries_]) {
	assert(table_ != NULL);

}

template <class T>
HashTable<T>::~HashTable() {

	if (table_ != NULL) {
		delete[] table_;
		table_ = NULL;
		hashentries_ = 0;
	}

}

template <class T>
void HashTable<T>::clear() {

	for (unsigned int i = 0; i < hashentries_; i++) {
		if (table_[i].count == 0) continue;
		else table_[i].count = 0;
	}
	elements_ = 0;

}

template <class T>
uint32_t HashTable<T>::size() {
	return elements_;
}

template <class T>
void HashTable<T>::insert(const T &node_id) {

	int pos = this->hash(node_id);

	if (table_[pos].count == table_[pos].size) {
		uint32_t *old = table_[pos].entries;
		table_[pos].entries = new uint32_t[table_[pos].size * 2];
		memcpy(table_[pos].entries, old, table_[pos].size * sizeof(uint32_t));
		delete[] old;
		table_[pos].count = table_[pos].size;
		table_[pos].size *= 2;
	}

	table_[pos].entries[table_[pos].count] = node_id;
	// table_[pos].entries.enstack(node_id);
	table_[pos].count++;
	elements_++;

}

template <class T>
bool HashTable<T>::search(const T& entry_id) {

	int pos = this->hash(entry_id);
	Bucket *temp = &table_[pos];

	for (int i = 0; i < temp->count; i++) {
		if (entry_id == temp->entries[i])
			return true;
	}

	return false;

}

template <class T>
bool HashTable<T>::searchInsert(const T &entry_id) {
    int pos = this->hash(entry_id);
    Bucket *temp = &table_[pos];

    for (int i = 0; i < temp->count; i++) {
        if (entry_id == temp->entries[i])
            return false;
    }
    if (temp->count == temp->size) {
        uint32_t *old = temp->entries;
        temp->entries = new uint32_t[temp->size * 2];
        memcpy(temp->entries, old, temp->size * sizeof(uint32_t));
        delete[] old;
        temp->count = temp->size;
        temp->size *= 2;
    }

    temp->entries[temp->count] = entry_id;
	// temp->entries.enstack(entry_id);
    temp->count++;
    elements_++;

    return true;
}

template <class T>
void HashTable<T>::print() {

	Bucket *temp;

	for (unsigned int i = 0; i < hashentries_; i++) {
		cout << "bucket[" << i << "]:" << endl;
		temp = &table_[i];
		for (int i = 0; i < temp->count; i++)
			cout << temp->entries[i] << endl;
	}

}


#endif
