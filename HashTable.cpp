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

uint32_t HashTable::hash(uint32_t& id) {
	return id % hashentries_;
}


void HashTable::insert(uint32_t &node_id) {

	int pos = this->hash(node_id);

	if (table_[pos].count == table_[pos].size - 1) {
		uint32_t *old = table_[pos].entries;
		table_[pos].entries = new uint32_t[table_[pos].size * 2];
		memcpy(table_[pos].entries, old, table_[pos].size);
		delete[] old;
		table_[pos].count = table_[pos].size;
		table_[pos].size *= 2;
	}

	table_[pos].entries[table_[pos].count] = node_id;
	table_[pos].count++;
	elements_++;

}

bool HashTable::search(uint32_t& entry_id) {

	int pos = this->hash(entry_id);
	Bucket *temp = &table_[pos];

	for (int i = 0; i < temp->count; i++) {
		if (entry_id == temp->entries[i])
			return true;
	}

	return false;

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
