#include <iostream>
#include <stdint.h>
#include "ShortestPath.h"

using namespace std;

//9721, 70537
int ShortestPath::creat = 0;

ShortestPath::ShortestPath(Graph& gr, uint32_t &hashSize) : prGraph(gr), hash_size(hashSize), dirF('F'), dirB('B'),
										distanceFront(0), distanceBack(0), clevelB(0), clevelF(0), clevelF1(0), clevelB1(0), exploredSet(NULL) {
	frontierFront = new LinkedList<uint32_t>();
	assert(frontierFront != NULL);
	frontierBack = new LinkedList<uint32_t>();
	assert(frontierBack != NULL);
	if (ShortestPath::creat == 0) {
		exploredSet = new HashTable(hash_size);
		assert(exploredSet != NULL);
		ShortestPath::creat++;
	}
}

ShortestPath::~ShortestPath() {
	if (frontierFront != NULL)
		delete frontierFront;
	if (frontierBack != NULL)
		delete frontierBack;
	if (exploredSet != NULL)
		delete exploredSet;
	frontierBack = NULL;
	frontierFront = NULL;
	exploredSet = NULL;
}

int ShortestPath::expand(uint32_t& nodeId, LinkedList<uint32_t> *frontier, char& dir) {
	/*Expand a node, adding its neighbors to the frontier and marking them as visited,
	or return solution cost, if we reached a node already visited from the other side*/

	uint32_t tempId;
	path_entry *data;
	NodeArray *neighbors = prGraph.getNeighbors(nodeId, dir);

	for (int i = 0; i < neighbors->size; i++) {
		tempId = neighbors->array[i];
		// if (exploredSet[tempId] != NULL) {
		if (exploredSet->search(tempId, &data)) {
			if (data->direction != dir) {
				delete neighbors;
				return data->pathCost + ((dir == 'F') ? distanceFront : distanceBack) + 1;
			}
		} else {
			unsigned int dist = ((dir == 'F') ? distanceFront : distanceBack) + 1;
			data = new path_entry(tempId, nodeId, dist, dir);
			exploredSet->insert(data);
			// exploredSet[tempId] = new path_entry(tempId, nodeId, dist, dir);
			frontier->push_back(tempId);
			if (dir == 'F')
				clevelF1++;
			else
				clevelB1++;
		}
	}
	delete neighbors;
	return -3;
}

int ShortestPath::step(LinkedList<uint32_t> *frontier, char& dir) {
	uint32_t nodeId = frontier->pop();
	if (dir == 'F')
		clevelF--;
	else
		clevelB--;
	return expand(nodeId, frontier, dir);
}

int ShortestPath::shortestPath(uint32_t& source, uint32_t& target) {
	
	if (source == target)
		return 0;
	
	int res = 0;
	frontierFront->push_back(source);
	clevelF = 1;
	frontierBack->push_back(target);
	clevelB = 1;
	path_entry *node = new path_entry(source, source, distanceFront, dirF);
	exploredSet->insert(node);
	// exploredSet[source] = new path_entry(source, source, distanceFront, dirF);
	node = new path_entry(target, target, distanceBack, dirB);
	exploredSet->insert(node);
	// exploredSet[target] = new path_entry(target, target, distanceBack, dirB);

	while (true) {

		//no solution, return failure
		if (frontierFront->empty() || frontierBack->empty())
			return -1;

		if (distanceFront <= distanceBack) {
			res = step(frontierFront, dirF);
			if (res != -3)
				return res;
			if (clevelF == 0) {
				++distanceFront;
				clevelF = clevelF1;
				clevelF1 = 0;
			}			
		} else if (distanceFront > distanceBack) {
			res = step(frontierBack, dirB);
			if (res != -3)
				return res;
			if (clevelB == 0) {
				++distanceBack;
				clevelB = clevelB1;
				clevelB1 = 0;
			}
		}
	}

	return -1;
}

void ShortestPath::reset() {
	distanceFront = 0;
	distanceBack = 0;
	clevelB = 0;
	clevelB1 = 0;
	clevelF = 0;
	clevelF1 = 0;
	if (frontierFront != NULL) {
		delete frontierFront;
		frontierFront = new LinkedList<uint32_t>();
	}
	if (frontierBack != NULL) {
		delete frontierBack;
		frontierBack = new LinkedList<uint32_t>();
	}
	exploredSet->iterandel();
}

void ShortestPath::init(const uint32_t &hashSize) {
	exploredSet = new HashTable(hashSize);
	assert(exploredSet != NULL);
}

uint32_t ShortestPath::determineHashSize() {
	uint32_t hashEntries = prGraph.getNodes() / 2;
	if (hashEntries % 2) {
		hashEntries++;
	}
	return hashEntries;
}