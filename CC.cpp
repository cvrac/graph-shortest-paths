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
    uint32_t cc_id = 0;
    for (uint32_t start_node = 0 ; start_node < total_nodes ; start_node++) {
        if (! graph_.checkMarkVisitedNode(start_node, 'A', visit_version_)) {
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
                if (graph_.checkMarkVisitedNode(node, 'A', visit_version_)) {
                    frontier_.enqueue(node);
                    ccindex_[node] = cc_id;
                }
            }
        }
        if (first) {
            first = false;
        }
    }
    update_index_.init(cc_id+1);
    update_index_.setElements(cc_id+1);
}

void CC::insertNewEdge(const uint32_t &source_node, const uint32_t &target_node) {
    assert(source_node < ccindex_.getElements() && target_node < ccindex_.getElements()); // Temp assert. Should always succeed according to them
    uint32_t min = ccindex_[source_node];
    uint32_t max = ccindex_[target_node];
    if (min == max) {
        return;
    }
/*    uint32_t initial_comp1_neighbors_elements = update_index_[comp1].getElements();
    uint32_t initial_comp2_neighbors_elements = update_index_[comp2].getElements();

    /* Make sure they components aren't already connected.
     * If they are, they will definitely have the same number of component neighbors,
     * so skip search otherwise *
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
    }*/

    if (min > max) {
        uint32_t temp = min;
        min = max;
        max = temp;
    }
    while (update_index_[min].neighbor_exists_) {
        if (update_index_[min].neighbor_ == max) {
            return;
        } else if (update_index_[min].neighbor_ < max) {
            min = update_index_[min].neighbor_;
        }
        else {
            if (! update_index_[min].ptr_exists_) {
                update_index_[min].ptr_ = max;
                update_index_[min].ptr_exists_ = true;
            }
            uint32_t base = update_index_[min].ptr_;
            uint32_t temp = max;
            max = update_index_[min].neighbor_;
            min = temp;
            if (update_index_[base].neighbor_ == min) {
                return;
            }
            while (update_index_[base].ptr_exists_) {
                base = update_index_[base].ptr_;
                if (update_index_[base].neighbor_ == min) {
                    return;
                }
            }
            update_index_[base].ptr_ = min;
            update_index_[base].ptr_exists_ = true;
        }
    }
    update_index_[min].neighbor_ = max;
    update_index_[min].neighbor_exists_ = true;
}

bool CC::sameConnectedComponent(const uint32_t &source_node, const uint32_t &target_node) {
    count++;
    queries_count_++;
    uint32_t min = ccindex_[source_node];
    uint32_t max = ccindex_[target_node];
    if (min == max) {
        return true;
    }
    update_index_use_count_++;
/*    uint32_t initial_comp1_neighbors_elements = update_index_[comp1].getElements();
    uint32_t initial_comp2_neighbors_elements = update_index_[comp2].getElements();

    if (initial_comp1_neighbors_elements == initial_comp2_neighbors_elements && initial_comp1_neighbors_elements) {
        if (update_index_[comp1].search(comp2)) {
            return true;
        }
    }
    return false;*/
    if (min > max) {
        uint32_t temp = min;
        min = max;
        max = temp;
    }
    while (update_index_[min].neighbor_exists_) {
        if (update_index_[min].neighbor_ == max) {
            return true;
        } else if (update_index_[min].neighbor_ < max) {
            min = update_index_[min].neighbor_;
        }
        else {
            if (! update_index_[min].ptr_exists_) {
                return false;
            }
            uint32_t base = update_index_[min].ptr_;
            uint32_t temp = max;
            max = update_index_[min].neighbor_;
            min = temp;
            if (update_index_[base].neighbor_ == min) {
                return true;
            }
            while (update_index_[base].ptr_exists_) {
                base = update_index_[base].ptr_;
                if (update_index_[base].neighbor_ == min) {
                    return true;
                }
            }
        }
    }
    return false;
}

void CC::reset() {
    uint32_t total_nodes = graph_.getNodes();
    ccindex_.init(total_nodes);
    ccindex_.setElements(total_nodes);
    queries_count_ = 0;
    update_index_use_count_ = 0;
    visit_version_++;
}

void CC::print() {
    for (uint32_t n = 0 ; n < graph_.getNodes() ; n++) {
        cout << n << " " << ccindex_[n] << "\n";
    }
    cout << "Updates: \n";
    for (uint32_t n = 0 ; n < update_index_.getElements() ; n++) {
        cout << n << ":";
        update_index_[n].print();
        cout << "\n";
    }
    cout << endl;
    cout << "Nodes are " << graph_.getNodes() << endl;
}

void CC::UpdateCell::print() {
    cout << (neighbor_exists_? " true" : " false") << " " << neighbor_;
}