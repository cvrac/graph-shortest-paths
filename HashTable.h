#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdint.h>
#include "LinkedList.h"
#include "PathEntry.h"

class HashTable {
	uint32_t hashentries;
	uint32_t _elements;
	struct HashEntry {
		uint32_t nodeId;
		path_entry nodeEntry;
		HashEntry(uint32_t& entry_id, uint32_t &parent_id, unsigned int &cost, char &dir);
		~HashEntry();
		void update(uint32_t& parentId, unsigned int &cost, char &dir);
	};
	friend std::ostream& operator<<(std::ostream& out, const HashEntry& d);
	friend bool operator== (const HashEntry& e1, const HashEntry& e2);
	LinkedList<HashEntry> *t_hash;
public:
	HashTable(const uint32_t& numofbucks);
	~HashTable();
	int size();
	// void insert(path_entry *nodeEntry);
	void insert(uint32_t &nodeId, uint32_t &parentId, unsigned int &pathCost, char &direction);
	bool search(uint32_t& entry_id, path_entry **data);
	void print();
	void iterandel();
	uint32_t hash(uint32_t& id);
};

#endif
