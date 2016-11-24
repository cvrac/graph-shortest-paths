#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdint.h>

#include "HashTable.hpp"
#include "Graph.hpp"
#include "Array.hpp"
#include "Garray.hpp"

class ShortestPath {

public:
	ShortestPath(Graph &gr, uint32_t &hashsize);
	~ShortestPath();
	int shortestPath(uint32_t &source, uint32_t &target);
	void reset();

private:
	int hash_size;
	HashTable<uint32_t> explored_set_;
	HashTable<uint32_t> explored_set_x;
	unsigned int clevelf_, clevelf1_;
	unsigned int clevelb_, clevelb1_;
	Graph &pr_graph_;
	Garray<uint32_t> frontier_front_;
	Garray<uint32_t> frontier_back_;
	unsigned int distance_front_;
	unsigned int distance_back_;
	char dirf_;
	char dirb_;
};

#endif
