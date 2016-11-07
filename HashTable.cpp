#include <iostream>
#include <cassert>
#include <cstring>
#include "HashTable.h"

using namespace std;

HashTable::HashEntry::HashEntry(uint32_t& id,  uint32_t &parent_id, unsigned int &cost, char &dir) : nodeId(id), nodeEntry(nodeId, parent_id, cost, dir) { }

HashTable::HashEntry::~HashEntry() {}

void HashTable::HashEntry::update(uint32_t& parentId, unsigned int &cost, char &dir) {
	nodeEntry.update(nodeId, parentId, cost, dir);
}


HashTable::HashTable(const uint32_t& numofbucks) : hashentries(numofbucks), _elements(0) {

	t_hash = new LinkedList<HashEntry> [hashentries];
	assert(t_hash != NULL);

}

HashTable::~HashTable() {

	if (t_hash != NULL) {
		delete[] t_hash;
		t_hash = NULL;
		hashentries = 0;
	}
}

void HashTable::iterandel() {
	for (unsigned int i = 0; i < hashentries; i++) {
		if (t_hash[i].empty() == true)
			continue;
		else
			t_hash[i].clear();
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
	HashEntry qq(nodeId, parentId, pathCost, direction);
	t_hash[pos].push_back(qq);
	_elements++;
}

bool HashTable::search(uint32_t& entry_id, path_entry **data) {
	int pos = this->hash(entry_id);
	char f = 'f';
	unsigned int d = 0;
	HashEntry temp(entry_id, entry_id, d, f);
	HashEntry *tempx;
	tempx = t_hash[pos].member(temp);
	if (tempx != NULL)
		*data = &(tempx->nodeEntry);
	return tempx != NULL;
}


void HashTable::print() {
	for (unsigned int i = 0; i < hashentries; i++) {
		if (t_hash[i].empty()) continue;
		cout << "bucket[" << i << "]:" << endl;
		t_hash[i].print();
	}
}

ostream& operator<<(ostream& out, const HashTable::HashEntry& d) {
	out << d.nodeEntry << endl;
	return out;
}

bool operator== (const HashTable::HashEntry& e1, const HashTable::HashEntry& e2) {
	return e1.nodeId == e2.nodeId;
}


// int main(void) {
// 	uint32_t i = 5;
// 	char b = 'f';
// 	unsigned int c = 5;
// 	int size = 11;
// 	HashTable table(size);
// 	table.insert(i, i, c, b);
// 	i = 10;
// 	table.insert(i, i, c, b);
// 	table.print();
// 	path_entry *data = NULL;
// 	if (table.search(i, &data)) {
// 		cout << "found" << endl;
// 		cout << *data << endl;
// 	}
// }
