#include "CC.hpp"

#include <assert.h>

#include <iostream>

using namespace std;

CC::~CC() {}

void CC::estimateConnectedComponents() {
    this->reset();
    uint32_t total_nodes = graph_.getNodes();
    assert(total_nodes);

    for (uint32_t start_node = 0, cc_id = 0 ; start_node < total_nodes ; start_node++) {
        if (! graph_.markVisitedNode(start_node, visited_flag_)) {
            continue;
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
        if (!cc_id) {
            cc_id++;
        }
    }
}

void CC::insertNewEdge(const uint32_t &source_node, const uint32_t &target_node) {
    uint32_t min = source_node;
    uint32_t max = target_node;
    if (target_node < min) {
        min = target_node;
        max = source_node;
    }
    assert(max < ccindex_.getElements()); // Temp assert. improve code after assert removal
    uint32_t min_comp = ccindex_[source_node];
    uint32_t max_comp = ccindex_[target_node];
    if (min_comp != max_comp) {
        if (min == target_node) {
            uint32_t temp = min_comp;
            min_comp = max_comp;
            max_comp = temp;
        }
        if (update_index_[min_comp].merged_with == NULL) {
            update_index_[min_comp].merged_with = new HashTable<uint32_t>(HASH_SIZE);
        }
        update_index_[min_comp].merged_with->insert(max_comp);
    }
}

void CC::reset() {
    uint32_t total_nodes = graph_.getNodes();
    ccindex_.init(total_nodes);
    ccindex_.setElements(total_nodes);
    update_index_.init(total_nodes);
    update_index_.setElements(total_nodes);
    frontier_.clear();
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
        if (update_index_[n].merged_with != NULL) {
            update_index_[n].merged_with->print();
        }
        cout << "\n\n";
    }
    cout << endl;
    cout << "Nodes are " << graph_.getNodes() << endl;
}