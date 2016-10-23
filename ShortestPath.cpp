#include <iostream>
#include <stdint.h>
#include "ShortestPath.h"

ShortestPath::ShortestPath(Graph& gr) {
	prGraph = gr;
	frontierFront = new LinkedList();
	assert(frontierFront != NULL);
	frontierBack = new LinkedList();
	assert(frontierBack != NULL);
	int i = 10;
	exploredSet = new HashTable(i);
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

void ShortestPath::expand(uint32_t& nodeId, LinkedList<uint32_t>& frontier) {
	uint32_t tempId;

}

void ShortestPath::step(LinkedList<uint32_t>& frontier) {
	uint32_t nodeId = frontier.pop();
	expand(nodeId, frontier);
}

int ShortestPath::shortestPath(uint32_t& source, uint32_t& target) {
	frontierFront.push_back(source);
	frontierBack.push_back(target);
	path_entry *node = new path_entry(source, source, distanceFront, 'F');
	exploredSet->insert(node);
	node = new path_entry(target, target, distanceBack, 'B');
	exploredSet->insert(node);

	while (true) {

		//no solution, return failure
		if (frontierFront.empty() || frontierBack.empty())
			return -1;

		if (distanceFront < distanceBack) {
			step(frontierFront);
			distanceFront++;
		} else if (distanceFront > distanceBack) {
			step(frontierBack);
			distanceBack++;
		} else if (distanceFront == distanceBack) {
			step(frontierFront);
			distanceFront++;
			step(frontierBack);
			distanceBack++;
		}

	}
}

