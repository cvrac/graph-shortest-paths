#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <stdint.h>

#include "HashTable.hh"
#include "Graph.hh"
#include "Garray.hh"
#include "SCC.hh"
#include "GrailIndex.hh"

class GrailIndex;

class ShortestPath {

public:
	friend class SCC;
	ShortestPath(Graph &gr, SCC &comp, GrailIndex &grail);
	~ShortestPath();
	int shortestPath(uint32_t &source, uint32_t &target, const char &mode, const uint32_t &current_version);
	void reset();
	void init() {explored_set_.init(pr_graph_.getNodes('N'));}
	void increaseExploreSet() {explored_set_.update(pr_graph_.getNodes('N'));}

private:
	unsigned int clevelf_, clevelf1_;
	unsigned int clevelb_, clevelb1_;
	Graph &pr_graph_;
	SCC &strongly_conn_;
	GrailIndex &grail_;
	Garray<uint32_t> frontier_front_;
	Garray<uint32_t> frontier_back_;
	ExploredSet explored_set_;
	unsigned int distance_front_;
	unsigned int distance_back_;
	char dirf_;
	char dirb_;
	unsigned long long visit_version_;
};

#endif
