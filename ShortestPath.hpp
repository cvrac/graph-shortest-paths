#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdint.h>
#include "HashTable.hpp"
#include "PathEntry.hpp"
#include "Graph.hpp"
#include "Queue.hpp"

class ShortestPath {
private:
	int expand(uint32_t &nodeid, Queue &frontier, char &dir);
	int step(Queue &frontier, char &dir);

	int hash_size;
	unsigned int clevelf_, clevelf1_;
	unsigned int clevelb_, clevelb1_;
	Graph &pr_graph_;
	Queue frontier_front_;
	Queue frontier_back_;
	HashTable explored_set_;
	unsigned int distance_front_;
	unsigned int distance_back_;
	char dirf_;
	char dirb_;
public:
	ShortestPath(Graph &gr, uint32_t &hashsize);
	~ShortestPath();
	int shortestPath(uint32_t &source, uint32_t &target);
	void reset();
};

#endif
