#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdint.h>
#include "HashTable.h"
#include "PathEntry.h"
#include "Graph.h"

class ShortestPath {
private:
	Graph& prGraph;
	LinkedList<uint32_t> frontierFront;
	LinkedList<uint32_t> frontierBack;
	HashTable exploredSet;
	unsigned int distanceFront;
	unsigned int distanceBack;
	bool interesection();
	void expand(uint32_t& nodeId);
	void step();
public:
	ShortestPath(Graph& gr);
	int shortestPath(uint32_t& source, uint32_t& target);
}

#endif