#include "HashTable.hpp"

#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

HashTable::Bucket::Bucket() : entries(new uint32_t[16]), count(0), size(16) {

	assert(entries != NULL);

}

HashTable::Bucket::~Bucket() {

	delete[] entries;
	entries = NULL;

}


HashTable::HashTable(const uint32_t& numofbucks) : hashentries_(numofbucks), elements_(0),
	table_(new Bucket[hashentries_]) {
	assert(table_ != NULL);

}

HashTable::~HashTable() {

	if (table_ != NULL) {
		delete[] table_;
		table_ = NULL;
		hashentries_ = 0;
	}

}

void HashTable::clear() {

	for (unsigned int i = 0; i < hashentries_; i++) {
		if (table_[i].count == 0) continue;
		else table_[i].count = 0;
	}
	elements_ = 0;

}

uint32_t HashTable::size() {
	return elements_;
}

void HashTable::insert(const uint32_t &node_id) {

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
	table_[pos].count++;
	elements_++;

}

bool HashTable::search(const uint32_t& entry_id) {

	int pos = this->hash(entry_id);
	Bucket *temp = &table_[pos];

	for (int i = 0; i < temp->count; i++) {
		if (entry_id == temp->entries[i])
			return true;
	}

	return false;

}

bool HashTable::searchInsert(const uint32_t &entry_id) {
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
    temp->count++;
    elements_++;

    return true;
}

void HashTable::print() {

	Bucket *temp;

	for (unsigned int i = 0; i < hashentries_; i++) {
		cout << "bucket[" << i << "]:" << endl;
		temp = &table_[i];
		for (int i = 0; i < temp->count; i++)
			cout << temp->entries[i] << endl;
	}

}
