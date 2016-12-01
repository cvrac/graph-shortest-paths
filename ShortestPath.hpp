#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdint.h>

#include "HashTable.hpp"
#include "Graph.hpp"
#include "Garray.hpp"
#include "SCC.hpp"

class ShortestPath {

public:
	friend class SCC;
	ShortestPath(Graph &gr, SCC &comp);
	~ShortestPath();
	int shortestPath(uint32_t &source, uint32_t &target, char mode);
	void reset();

private:
	unsigned int clevelf_, clevelf1_;
	unsigned int clevelb_, clevelb1_;
	Graph &pr_graph_;
	SCC &strongly_conn_;
	Garray<uint32_t> frontier_front_;
	Garray<uint32_t> frontier_back_;
	unsigned int distance_front_;
	unsigned int distance_back_;
	char dirf_;
	char dirb_;
	unsigned long long visit_version_;

};

#endif
