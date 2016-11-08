#ifndef GRAPHSHORTESTPATHS_HASHTABLE_H
#define GRAPHSHORTESTPATHS_HASHTABLE_H

#include <iostream>

#include <cstdlib>
#include <string>
#include <stdint.h>

#include "PathEntry.hpp"

class HashTable {
	uint32_t hashentries_;
	uint32_t elements_;
	struct Bucket {
		Bucket();
		~Bucket();

		int count;
		int size;
		PathEntry *entries;
	};
	Bucket *table_;
public:
	HashTable(const uint32_t &numofbucks);
	~HashTable();
	int size();
	void insert(uint32_t &nodeid, uint32_t &parentid, unsigned int &pathcost, char &direction);
	bool search(uint32_t &entry_id, PathEntry **data);
	void print();
	void clear();
	uint32_t hash(uint32_t &id);
};

#endif
