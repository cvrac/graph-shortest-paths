#include <iostream>
#include <cassert>
#include <cstring>
#include "HashTable.h"

using namespace std;

// HashTable::HashEntry::HashEntry(uint32_t& id,  uint32_t &parent_id, unsigned int &cost, char &dir) : nodeId(id), nodeEntry(nodeId, parent_id, cost, dir) { }
//
// HashTable::HashEntry::~HashEntry() {}
//
// void HashTable::HashEntry::update(uint32_t& parentId, unsigned int &cost, char &dir) {
// 	nodeEntry.update(nodeId, parentId, cost, dir);
// }

HashTable::Bucket::Bucket() : count(0), size(4) {
	entries = new path_entry[size];
	assert(entries != NULL);
}

HashTable::Bucket::~Bucket() {
	delete[] entries;
	entries = NULL;
}


HashTable::HashTable(const uint32_t& numofbucks) : hashentries(numofbucks), _elements(0) {

	// t_hash = new LinkedList<HashEntry> [hashentries];
	// assert(t_hash != NULL);
	t_hash = new Bucket[hashentries];
	assert(t_hash != NULL);
}

HashTable::~HashTable() {

	if (t_hash != NULL) {
		delete[] t_hash;
		t_hash = NULL;
		hashentries = 0;
	}
}

void HashTable::clear() {
	for (unsigned int i = 0; i < hashentries; i++) {
		if (t_hash[i].count == 0) continue;
		else t_hash[i].count = 0;
		// if (t_hash[i].empty() == true)
		// 	continue;
		// else
		// 	t_hash[i].clear();
	}
	_elements = 0;
}

int HashTable::size() {
	return _elements;
}

uint32_t HashTable::hash(uint32_t& id) {
	return id % hashentries;
}


void HashTable::insert(uint32_t &nodeId, uint32_t &parentId, unsigned int &pathCost, char &direction) {
	int pos = this->hash(nodeId);
	path_entry qq(nodeId, parentId, pathCost, direction);
	// cout << "here" << endl;
	if (t_hash[pos].count == t_hash[pos].size - 1) {
		path_entry *old = t_hash[pos].entries;
		t_hash[pos].entries = new path_entry[t_hash[pos].size * 2];
		memcpy(t_hash[pos].entries, old, t_hash[pos].size);
		delete[] old;
		t_hash[pos].count = t_hash[pos].size;
		t_hash[pos].size *= 2;
	}
	t_hash[pos].entries[t_hash[pos].count] = qq;
	t_hash[pos].count++;
	// HashEntry qq(nodeId, parentId, pathCost, direction);
	// t_hash[pos].push_back(qq);
	_elements++;
}

bool HashTable::search(uint32_t& entry_id, path_entry **data) {
	// cout << "here" << endl;
	int pos = this->hash(entry_id);
	char f = 'f';
	unsigned int d = 0;
	path_entry qq(entry_id, entry_id, d, f);
	Bucket *temp = &t_hash[pos];
	for (int i = 0; i < temp->count; i++) {
		if (qq.nodeId == temp->entries[i].nodeId) {
			*data = &(temp->entries[i]);
			return true;
		}
	}
	return false;
	// HashEntry temp(entry_id, entry_id, d, f);
	// HashEntry *tempx;
	// tempx = t_hash[pos].member(temp);
	// if (tempx != NULL)
	// 	*data = &(tempx->nodeEntry);
	// return tempx != NULL;
}


void HashTable::print() {
	Bucket *temp;
	for (unsigned int i = 0; i < hashentries; i++) {
		// if (t_hash[i].empty()) continue;
		cout << "bucket[" << i << "]:" << endl;
		// t_hash[i].print();
		temp = &t_hash[i];
		for (int i = 0; i < temp->count; i++)
			cout << temp->entries[i] << endl;
	}
}

// ostream& operator<<(ostream& out, const HashTable::HashEntry& d) {
// 	out << d.nodeEntry << endl;
// 	return out;
// }
//
// bool operator== (const HashTable::HashEntry& e1, const HashTable::HashEntry& e2) {
// 	return e1.nodeId == e2.nodeId;
// }
