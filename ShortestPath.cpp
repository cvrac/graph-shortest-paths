#include <iostream>
#include <stdint.h>
#include "ShortestPath.h"

using namespace std;

ShortestPath::ShortestPath(Graph& gr) : prGraph(gr), hash_size(1000), dirF('F'), dirB('B') {
	frontierFront = new LinkedList<uint32_t>();
	assert(frontierFront != NULL);
	frontierBack = new LinkedList<uint32_t>();
	assert(frontierBack != NULL);
	exploredSet = new HashTable(hash_size);
	assert(exploredSet != NULL);
	distanceFront = 0;
	distanceBack = 0;
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

//	cout << "expanding " << nodeId << endl;
	uint32_t tempId;
	path_entry *data;
	NodeArray *neighbors = prGraph.getNeighbors(nodeId, dir);

	for (int i = 0; i < neighbors->size; i++) {
		tempId = neighbors->array[i];
//		cout << "neighbor " << tempId << endl;
		if (exploredSet->search(tempId, &data)) {
//			cout << "node exists" << endl;
//			cout << data->direction << endl;
//			cout << dir << endl;
			if (data->direction != dir) {
//				cout << "return cost" << endl;
				delete neighbors;
				return data->pathCost + ((dir == 'F') ? distanceFront : distanceBack);
			}
		} else {
			data = new path_entry(tempId, nodeId, (dir == 'F') ? distanceFront : distanceBack, dir);
			exploredSet->insert(data);
			frontier->push_back(tempId);
		}
//		exploredSet->print();
	}
	delete neighbors;
	return -2;
}

int ShortestPath::step(LinkedList<uint32_t> *frontier, char& dir) {
	uint32_t nodeId = frontier->pop();
	if (dir == 'F')
		++distanceFront;
	else
		++distanceBack;
	return expand(nodeId, frontier, dir);
}

int ShortestPath::shortestPath(uint32_t& source, uint32_t& target) {
	
	if (source == target)
		return 0;
	
	int res = 0;
	frontierFront->push_back(source);
	frontierBack->push_back(target);
	path_entry *node = new path_entry(source, source, distanceFront, dirF);
	exploredSet->insert(node);
	node = new path_entry(target, target, distanceBack, dirB);
	exploredSet->insert(node);

	while (true) {

		//no solution, return failure
		if (frontierFront->empty() || frontierBack->empty())
			return -1;

		if (distanceFront < distanceBack) {
			res = step(frontierFront, dirF);
			if (res != -2)
				return res;
//			distanceFront++;
		} else if (distanceFront > distanceBack) {
			res = step(frontierBack, dirB);
			if (res != -2)
				return res;
//			distanceBack++;
		} else if (distanceFront == distanceBack) {
			res = step(frontierFront, dirF);
			if (res != -2)
				return res;			
//			distanceFront++;
			res = step(frontierBack, dirB);
			if (res != -2)
				return res;			
//			distanceBack++;
		}
	}

	return -1;
}

