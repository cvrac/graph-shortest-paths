#include <iostream>
#include <stdint.h>
#include "ShortestPath.h"

using namespace std;

//9721, 70537
int ShortestPath::creat = 0;

ShortestPath::ShortestPath(Graph& gr, uint32_t &hashSize) : hash_size(hashSize), dirF('F'), dirB('B'),
										distanceFront(0), distanceBack(0), clevelB(0), clevelF(0), clevelF1(0), clevelB1(0), exploredSet(hash_size), prGraph(gr) {
}

ShortestPath::~ShortestPath() { }

int ShortestPath::expand(uint32_t& nodeId, Queue &frontier, char& dir) {
	/*Expand a node, adding its neighbors to the frontier and marking them as visited,
	or return solution cost, if we reached a node already visited from the other side*/

	uint32_t tempId;
	unsigned int dist;
	path_entry *data;
	NodeArray *neighbors = prGraph.getNeighbors(nodeId, dir);

	for (int i = 0; i < neighbors->size; i++) {
		tempId = neighbors->array[i];
		// if (exploredSet[tempId] != NULL) {
		if (exploredSet.search(tempId, &data)) {
			if (data->direction != dir) {
				delete neighbors;
				return data->pathCost + ((dir == 'F') ? distanceFront : distanceBack) + 1;
			}
		} else {
			dist = ((dir == 'F') ? distanceFront : distanceBack) + 1;
			exploredSet.insert(tempId, nodeId, dist, dir);
			// exploredSet[tempId] = new path_entry(tempId, nodeId, dist, dir);
			frontier.push(tempId);
			if (dir == 'F')
				clevelF1++;
			else
				clevelB1++;
		}
	}
	delete neighbors;
	return -3;
}

int ShortestPath::step(Queue &frontier, char& dir) {
	uint32_t nodeId = frontier.pop();
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
	uint32_t nodeId, tempId;
	NodeArray *neighbors;
	unsigned int dist;
	path_entry *data;
	frontierFront.push(source);
	clevelF = 1;
	frontierBack.push(target);
	clevelB = 1;
	exploredSet.insert(source, source, distanceFront, dirF);
	exploredSet.insert(target, target, distanceBack, dirB);

	while (true) {

		//no solution, return failure
		if (frontierFront.empty() || frontierBack.empty())
			return -1;

		if (clevelF <= clevelB) {
			clevelF--;
			nodeId = frontierFront.pop();
			neighbors = prGraph.getNeighbors(nodeId, dirF);
			for (int i = 0; i < neighbors->size; i++) {
				tempId = neighbors->array[i];
				if (exploredSet.search(tempId, &data)) {
					if (data->direction != dirF) {
						delete neighbors;
						return data->pathCost + distanceFront + 1;
					}
				} else {
					dist = distanceFront + 1;
					exploredSet.insert(tempId, nodeId, dist, dirF);
					// exploredSet[tempId] = new path_entry(tempId, nodeId, dist, dir);
					frontierFront.push(tempId);
					clevelF1++;
				}
			}
			delete neighbors;
			// res = -3;
			// res = step(frontierFront, dirF);
			// if (res != -3)
			// 	return res;
			if (clevelF == 0) {
				++distanceFront;
				clevelF = clevelF1;
				clevelF1 = 0;
			}
		} else if (clevelF > clevelB) {
			clevelB--;
			nodeId = frontierBack.pop();
			NodeArray *neighbors = prGraph.getNeighbors(nodeId, dirB);
			for (int i = 0; i < neighbors->size; i++) {
				tempId = neighbors->array[i];
				// if (exploredSet[tempId] != NULL) {
				if (exploredSet.search(tempId, &data)) {
					if (data->direction != dirB) {
						delete neighbors;
						return data->pathCost + distanceBack + 1;
					}
				} else {
					dist = distanceBack + 1;
					exploredSet.insert(tempId, nodeId, dist, dirB);
					// exploredSet[tempId] = new path_entry(tempId, nodeId, dist, dir);
					frontierBack.push(tempId);
					clevelB1++;
				}
			}
			delete neighbors;
			// res = -3;
			// res = step(frontierBack, dirB);
			// if (res != -3)
			// 	return res;
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
	frontierFront.clear();
	frontierBack.clear();
	exploredSet.iterandel();
}

void ShortestPath::init(const uint32_t &hashSize) {
	// exploredSet = new HashTable(hashSize);
	// assert(exploredSet != NULL);
}

uint32_t ShortestPath::determineHashSize() {
	uint32_t hashEntries = prGraph.getNodes() / 2;
	if (hashEntries % 2) {
		hashEntries++;
	}
	return hashEntries;
}
