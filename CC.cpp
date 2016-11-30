#include "CC.hpp"

#include <assert.h>

#include <iostream>

using namespace std;

uint32_t count = 0;


CC::~CC() {}

void CC::estimateConnectedComponents() {
    this->reset();
    uint32_t total_nodes = graph_.getNodes();
    assert(total_nodes);

    bool first = true;
    for (uint32_t start_node = 0, cc_id = 0 ; start_node < total_nodes ; start_node++) {
        if (! graph_.markVisitedNode(start_node, visited_flag_)) {
            continue;
        }
        if (!first) {
            cc_id++;
        }
        ccindex_[start_node] = cc_id;
        frontier_.enqueue(start_node);
        while (! frontier_.isEmpty()) {
            uint32_t node = frontier_.popFront();
            Garray<uint32_t > &neighbors = graph_.getNeighbors(node, 'A');
            for (int i = 0; i < neighbors.getElements(); i++) {
                node = neighbors[i];
                if (graph_.markVisitedNode(node, visited_flag_)) {
                    frontier_.enqueue(node);
                    ccindex_[node] = cc_id;
                }
            }
        }
        if (first) {
            first = false;
        }
    }
}

void CC::insertNewEdge(const uint32_t &source_node, const uint32_t &target_node) {
    assert(source_node < ccindex_.getElements() && target_node < ccindex_.getElements()); // Temp assert. Should always succeed according to them
    uint32_t comp1 = ccindex_[source_node];
    uint32_t comp2 = ccindex_[target_node];
    if (comp1 == comp2) {
        return;
    }
    uint32_t initial_comp1_neighbors_elements = update_index_[comp1].getElements();
    uint32_t initial_comp2_neighbors_elements = update_index_[comp2].getElements();

    /* Make sure they components aren't already connected.
     * If they are, they will definitely have the same number of component neighbors,
     * so skip search otherwise */
    if (initial_comp1_neighbors_elements == initial_comp2_neighbors_elements) {
        if (update_index_[comp1].search(comp2)) {
            return;
        }
    }
    update_index_[comp1].pushBatch(update_index_[comp2].getArray(), initial_comp2_neighbors_elements);
    update_index_[comp1].enstack(comp2);
    for (uint32_t n = 0 ; n < initial_comp1_neighbors_elements ; n++) {
        update_index_[update_index_[comp1][n]].pushBatch(update_index_[comp2].getArray(), initial_comp2_neighbors_elements);
        update_index_[update_index_[comp1][n]].enstack(comp2);
    }

    update_index_[comp2].pushBatch(update_index_[comp1].getArray(), initial_comp1_neighbors_elements);
    update_index_[comp2].enstack(comp1);
    for (uint32_t n = 0 ; n < initial_comp2_neighbors_elements ; n++) {
        update_index_[update_index_[comp2][n]].pushBatch(update_index_[comp1].getArray(), initial_comp1_neighbors_elements);
        update_index_[update_index_[comp2][n]].enstack(comp1);
    }
}

bool CC::sameConnectedComponent(const uint32_t &source_node, const uint32_t &target_node) {
    count++;
    queries_count_++;
    uint32_t comp1 = ccindex_[source_node];
    uint32_t comp2 = ccindex_[target_node];
    if (comp1 == comp2) {
        return true;
    }
    update_index_use_count_++;
    uint32_t initial_comp1_neighbors_elements = update_index_[comp1].getElements();
    uint32_t initial_comp2_neighbors_elements = update_index_[comp2].getElements();

    if (initial_comp1_neighbors_elements == initial_comp2_neighbors_elements && initial_comp1_neighbors_elements) {
        if (update_index_[comp1].search(comp2)) {
            return true;
        }
    }
    return false;
}

void CC::reset() {
    uint32_t total_nodes = graph_.getNodes();
    ccindex_.init(total_nodes);
    ccindex_.setElements(total_nodes);
    update_index_.init(total_nodes);
    update_index_.setElements(total_nodes);
    queries_count_ = 0;
    update_index_use_count_ = 0;
    if (visited_flag_) {
        visited_flag_ = false;
    }
    else {
        visited_flag_ = true;
    }
}

void CC::print() {
    for (uint32_t n = 0 ; n < graph_.getNodes() ; n++) {
        cout << n << " " << ccindex_[n] << "\n";
    }
    cout << "Updates: \n";
    for (uint32_t n = 0 ; n < graph_.getNodes() ; n++) {
        cout << n << ":\n";
        update_index_[n].print();
        cout << "\n\n";
    }
    cout << endl;
    cout << "Nodes are " << graph_.getNodes() << endl;
}