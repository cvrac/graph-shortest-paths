#include "ShortestPath.hpp"

#include <iostream>
#include <stdint.h>

using namespace std;

ShortestPath::ShortestPath(Graph& gr, uint32_t &hashSize) : hash_size(hashSize),
	explored_set_(hash_size), explored_set_x(hash_size),
	clevelf_(0), clevelf1_(0),	clevelb_(0), clevelb1_(0), pr_graph_(gr),
	distance_front_(0), distance_back_(0), dirf_('F'), dirb_('B') {
}

ShortestPath::~ShortestPath() { }

int ShortestPath::shortestPath(uint32_t& source, uint32_t& target) {

	if (source == target)
		return 0;

	//initilizations of structures
	NodeArray *neighbors;
	uint32_t tempId, node_id;
	short int child_check;

	clevelf_ = 1;
	clevelb_ = 1;

	frontier_front_.push(source);
	frontier_back_.push(target);

	explored_set_.insert(source);
	explored_set_x.insert(target);

	while (true) {

		//no solution, return failure
		if (frontier_front_.empty() || frontier_back_.empty())
			return -1;

		child_check = (clevelf_ <= clevelb_) ? 1 : 0;
		switch (child_check) {
			case 1:
			node_id = frontier_front_.pop();
			--clevelf_;

			//expand node
			neighbors = pr_graph_.getNeighbors(node_id, dirf_);
			for (int i = 0; i < neighbors->size; i++) {
				tempId = neighbors->array[i];
				if (explored_set_x.search(tempId))  {
					delete neighbors;
					neighbors = NULL;
					return distance_front_ + distance_back_ + 1;
				} else if (explored_set_.searchInsert(tempId)) {
					//explored_set_.insert(tempId);
					frontier_front_.push(tempId);
					++clevelf1_;
				}
			}

			delete neighbors;
			neighbors = NULL;

			if (clevelf_ == 0) {
				++distance_front_;
				clevelf_ = clevelf1_;
				clevelf1_ = 0;
			}
			break;
			case 0:
			node_id = frontier_back_.pop();
			--clevelb_;

			//expand node
			neighbors = pr_graph_.getNeighbors(node_id, dirb_);
			for (int i = 0; i < neighbors->size; i++) {
				tempId = neighbors->array[i];
				if (explored_set_.search(tempId))  {
					delete neighbors;
					return distance_front_ + distance_back_ + 1;
				} else if (explored_set_x.searchInsert(tempId)) {
					//explored_set_x.insert(tempId);
					frontier_back_.push(tempId);
					++clevelb1_;
				}
			}

			delete neighbors;
			neighbors = NULL;

			if (clevelb_ == 0) {
				++distance_back_;
				clevelb_ = clevelb1_;
				clevelb1_ = 0;
			}
			break;
		}
	}

	return -1;
}

void ShortestPath::reset() {
	//clear structures for next queries
	distance_front_ = 0;
	distance_back_ = 0;
	clevelb_ = 0;
	clevelb1_ = 0;
	clevelf_ = 0;
	clevelf1_ = 0;
	frontier_front_.clear();
	frontier_back_.clear();
	explored_set_.clear();
	explored_set_x.clear();
}
