#ifndef GRAPHSHORTESTPATHS_HASHTABLE_H
#define GRAPHSHORTESTPATHS_HASHTABLE_H

#include <iostream>

#include <cstdlib>
#include <string>
#include <stdint.h>

class HashTable {

public:
	HashTable(const uint32_t &numofbucks);
	HashTable() : hashentries_(23), elements_(0), table_(NULL), table2(NULL) {}
	~HashTable();
	inline uint32_t size();
	void insert(uint32_t &nodeid);
	bool search(uint32_t &entry_id);
	void print();
	void clear();
	inline uint32_t hash(uint32_t &id);

private:
	struct Bucket {
		Bucket();
		~Bucket();

		uint32_t *entries;
		int count;
		int size;
	};

	uint32_t hashentries_;
	uint32_t elements_;
	Bucket *table_;
	HashTable *table2;
};

#endif
