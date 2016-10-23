#include <iostream>
#include <stdint.h>
#include "ShortestPath.h"

ShortestPath::ShortestPath(Graph& gr) {
	prGraph = gr;
	frontierFront = new LinkedList();
	frontierBack = new LinkedList();
	int i = 10;
	exploredSet = new HashTable(i);
	distanceFront = 0;
	distanceBack = 0;
}

bool ShortestPath::intersection() {

}

void ShortestPath::expand(uint32_t& nodeId) {

}

void ShortestPath::step() {

}

int ShortestPath::shortestPath(uint32_t& source, uint32_t& target) {
	frontierFront.push_back(source);
	frontierBack.push_back(target);

	while (true) {

		//no solution, return failure
		if (frontierFront.empty() || frontierBack.empty())
			return -1;

		if (distanceFront < distanceBack) {
			step(frontierFront);
		} else if (distanceFront > distanceBack) {
			step(frontierBack);
		} else if (distanceFront == distanceBack) {
			step(frontierFront);
			step(frontierBack);
		}

	}
}

