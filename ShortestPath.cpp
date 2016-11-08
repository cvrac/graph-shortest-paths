#include "ShortestPath.hpp"

#include <iostream>
#include <stdint.h>

using namespace std;

ShortestPath::ShortestPath(Graph& gr, uint32_t &hashSize) : hash_size(hashSize), dirf_('F'), dirb_('B'),
										distance_front_(0), distance_back_(0), clevelb_(0), clevelf_(0), clevelf1_(0), clevelb1_(0), explored_set_(hash_size), explored_set_x(hash_size), pr_graph_(gr) {
}

ShortestPath::~ShortestPath() { }

int ShortestPath::expand(uint32_t& node_id, Queue &frontier, char& dir) {
	/*Expand a node, adding its neighbors to the frontier and marking them as visited,
	or return solution cost, if we reached a node already visited from the other side*/

	// uint32_t tempId;
	// unsigned int dist;
	// PathEntry *data;
	// NodeArray *neighbors = pr_graph_.getNeighbors(node_id, dir);
	//
	// for (int i = 0; i < neighbors->size; i++) {
	// 	tempId = neighbors->array[i];
	// 	if (explored_set_.search(tempId, &data)) {
	// 		if (data->direction != dir) {
	// 			delete neighbors;
	// 			return data->path_cost + ((dir == 'F') ? distance_front_ : distance_back_) + 1;
	// 		}
	// 	} else {
	// 		// dist = ((dir == 'F') ? distance_front_ : distance_back_) + 1;
	// 		explored_set_.insert(tempId);
	// 		frontier.push(tempId);
	// 		if (dir == 'F')
	// 			clevelf1_++;
	// 		else
	// 			clevelb1_++;
	// 	}
	// }
	// delete neighbors;
	return -3;
}

int ShortestPath::step(Queue &frontier, char& dir) {
	uint32_t node_id = frontier.pop();
	// if (dir == 'F')
	// 	clevelf_--;
	// else
	// 	clevelb_--;
	return expand(node_id, frontier, dir);
}

int ShortestPath::shortestPath(uint32_t& source, uint32_t& target) {

	if (source == target)
		return 0;

	//initilizations of structures
	int res = 0;
	unsigned int dist;
	NodeArray *neighbors;
	uint32_t tempId, node_id;

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

		if (clevelf_ <= clevelb_) {

			node_id = frontier_front_.pop();
			clevelf_--;

			//expand node
			neighbors = pr_graph_.getNeighbors(node_id, dirf_);
			for (int i = 0; i < neighbors->size; i++) {
				tempId = neighbors->array[i];
				if (explored_set_x.search(tempId))  {
					delete neighbors;
					neighbors = NULL;
					return distance_front_ + distance_back_ + 1;
				} else if (!explored_set_.search(tempId)) {
					dist = distance_front_ + 1;
					explored_set_.insert(tempId);
					frontier_front_.push(tempId);
					clevelf1_++;
				}
			}

			delete neighbors;
			neighbors = NULL;

			if (clevelf_ == 0) {
				++distance_front_;
				clevelf_ = clevelf1_;
				clevelf1_ = 0;
			}

		} else if (clevelf_ > clevelb_) {

			node_id = frontier_back_.pop();
			clevelb_--;

			//expand node
			neighbors = pr_graph_.getNeighbors(node_id, dirb_);
			for (int i = 0; i < neighbors->size; i++) {
				tempId = neighbors->array[i];
				if (explored_set_.search(tempId))  {
					delete neighbors;
					return distance_front_ + distance_back_ + 1;
				} else if (!explored_set_x.search(tempId)) {
					dist = distance_back_ + 1;
					explored_set_x.insert(tempId);
					frontier_back_.push(tempId);
					clevelb1_++;
				}
			}

			delete neighbors;
			neighbors = NULL;

			if (clevelb_ == 0) {
				++distance_back_;
				clevelb_ = clevelb1_;
				clevelb1_ = 0;
			}

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
