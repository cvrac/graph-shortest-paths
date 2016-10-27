#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdint.h>
#include "HashTable.h"
#include "PathEntry.h"
#include "Graph.h"

class ShortestPath {
private:
	int hash_size;
	unsigned int clevelF, clevelF1;
	unsigned int clevelB, clevelB1;
	Graph& prGraph;
	LinkedList<uint32_t> *frontierFront;
	LinkedList<uint32_t> *frontierBack;
	HashTable *exploredSet;
	// path_entry **exploredSet;
	unsigned int distanceFront;
	unsigned int distanceBack;
	char dirF;
	char dirB;
	int expand(uint32_t& nodeId, LinkedList<uint32_t> * frontier, char& dir);
	int step(LinkedList<uint32_t> * frontier, char& dir);
public:
	ShortestPath(Graph& gr);
	~ShortestPath();
	int shortestPath(uint32_t& source, uint32_t& target);
};

#endif