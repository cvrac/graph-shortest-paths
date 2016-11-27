#include <iostream>

#include <assert.h>

#include "CC.hpp"

using namespace std;

CC::~CC() {}

void CC::estimateConnectedComponents() {
    this->reset();
    assert(graph_.outer_index_.getCurSize());
    uint32_t node = 1;

    frontier_outer_.enqueue(node);
    explored_set_.insert(node);


}

void CC::reset() {
    explored_set_.clear();
    frontier_outer_.clear();
    frontier_inner_.clear();
}