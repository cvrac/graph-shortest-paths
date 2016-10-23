#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdint.h>
#include "HashTable.h"
#include "PathEntry.h"

class ShortestPath {
private:
	LinkedList<uint32_t> frontierFront;
	LinkedList<uint32_t> frontierBack;
	HashTable exploredSet;
	bool interesection();
public:
	bool shortestPath(uint32_t& source, uint32_t& target);
}

#endif