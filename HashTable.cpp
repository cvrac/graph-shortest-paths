//
// entries = new uint32_t[size];#include <iostream>
#include <cassert>
#include <cstring>
#include "HashTable.hpp"

using namespace std;

HashTable::Bucket::Bucket() : count(0), size(16) {
	// entries = new PathEntry[size];
	entries = new uint32_t[size];
	assert(entries != NULL);
}

HashTable::Bucket::~Bucket() {

	delete[] entries;
	entries = NULL;

}


HashTable::HashTable(const uint32_t& numofbucks) : hashentries_(numofbucks), elements_(0) {

	table_ = new Bucket[hashentries_];
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

int HashTable::size() {
	return elements_;
}

uint32_t HashTable::hash(uint32_t& id) {
	return id % hashentries_;
}


void HashTable::insert(uint32_t &nodeId, uint32_t &parentId, unsigned int &pathCost, char &direction) {

	int pos = this->hash(nodeId);
	// PathEntry qq(nodeId, parentId, pathCost, direction);
	if (table_[pos].count == table_[pos].size - 1) {
		uint32_t *old = table_[pos].entries;
		// table_[pos].entries = new PathEntry[table_[pos].size * 2];
		table_[pos].entries = new uint32_t[table_[pos].size * 2];
		memcpy(table_[pos].entries, old, table_[pos].size);
		delete[] old;
		table_[pos].count = table_[pos].size;
		table_[pos].size *= 2;
	}
	table_[pos].entries[table_[pos].count] = nodeId;
	table_[pos].count++;
	elements_++;

}

bool HashTable::search(uint32_t& entry_id, PathEntry **data) {

	int pos = this->hash(entry_id);
	char f = 'f';
	unsigned int d = 0;
	// PathEntry qq(entry_id, entry_id, d, f);
	Bucket *temp = &table_[pos];
	for (int i = 0; i < temp->count; i++) {
		// if (qq.node_id == temp->entries[i].node_id) {
		if (entry_id == temp->entries[i]) {
			// *data = &(temp->entries[i]);
			return true;
		}
	}
	return false;

}

void HashTable::print() {

	Bucket *temp;
	// for (unsigned int i = 0; i < hashentries_; i++) {
	// 	cout << "bucket[" << i << "]:" << endl;
	// 	temp = &table_[i];
	// 	for (int i = 0; i < temp->count; i++)
	// 		cout << temp->entries[i] << endl;
	// }

}
