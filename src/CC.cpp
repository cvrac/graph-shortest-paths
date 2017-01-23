#include "CC.hpp"

#include <assert.h>

#include <iostream>

using namespace std;

CC::~CC() {}

void CC::estimateConnectedComponents() {
    if (! index_version_) {
        this->init();
    } else {
        this->reset();
    }
    uint32_t total_nodes = graph_.getNodes('N');
    assert(total_nodes);

    bool first = true;
    uint32_t cc_id = 0;
    for (uint32_t start_node = 0 ; start_node < total_nodes ; start_node++) {
        if (! explored_set_.checkMarkVisitedNode(start_node, index_version_, 'F')) {
            continue;
        }
        if (!first) {
            cc_id++;
        }
        ccindex_[start_node] = cc_id;
        frontier_.enstack(start_node);
        while (! frontier_.isEmpty()) {
            uint32_t node = frontier_.popBack();
            graph_.getNeighbors(node, 'A', 0, neighbors_);
            for (int i = 0; i < neighbors_.getElements(); i++) {
                node = neighbors_[i];
                if (explored_set_.checkMarkVisitedNode(node, index_version_, 'F')) {
                    frontier_.enstack(node);
                    ccindex_[node] = cc_id;
                }
            }
        }
        if (first) {
            first = false;
        }
    }
    //if (index_version_ == 1) {   // Omitting new/deletes with versioning barely helps
        update_index_.init(cc_id+1);
        update_index_.setElements(cc_id+1);
    //  }
}

void CC::insertNewEdge(const uint32_t &source_node, const uint32_t &target_node, const long &graph_version) {
    assert(source_node < ccindex_.getElements() && target_node < ccindex_.getElements()); // Temp assert. If failure, implement new node addition
    queries_count_++;
    uint32_t min = findNodeConnectedComponentID(source_node);
    uint32_t max = findNodeConnectedComponentID(target_node);
    if (min == max) {
        return;
    }
    update_index_use_count_++;
    if (min > max) {
        uint32_t temp = min;
        min = max;
        max = temp;
    }
    while (update_index_[min].index_version == index_version_ && update_index_[min].graph_version <= graph_version) {
        if (update_index_[min].neighbor == max) {
            return;
        } else if (update_index_[min].neighbor < max) {
            min = update_index_[min].neighbor;
        }
        else {
            uint32_t temp = max;
            max = update_index_[min].neighbor;
            min = temp;
        }
    }
    update_index_[min].neighbor = max;
    update_index_[min].index_version = index_version_;
    update_index_[min].graph_version = graph_version;
}

bool CC::sameConnectedComponent(const uint32_t &source_node, const uint32_t &target_node, const long &graph_version) {
    queries_count_++;
    uint32_t min = findNodeConnectedComponentID(source_node);
    uint32_t max = findNodeConnectedComponentID(target_node);;
    if (min == max) {
        return true;
    }
    update_index_use_count_++;
    if (min > max) {
        uint32_t temp = min;
        min = max;
        max = temp;
    }
    while (update_index_[min].index_version == index_version_ && update_index_[min].graph_version <= graph_version) {
        if (update_index_[min].neighbor == max) {
            return true;
        } else if (update_index_[min].neighbor < max) {
            min = update_index_[min].neighbor;
        }
        else {
            uint32_t temp = max;
            max = update_index_[min].neighbor;
            min = temp;
        }
    }
    return false;
}

void CC::reset() {
    uint32_t total_nodes = graph_.getNodes('N');
    ccindex_.increaseSize(total_nodes);
    ccindex_.setElements(total_nodes);
    explored_set_.update(total_nodes);
    queries_count_ = 0;
    update_index_use_count_ = 0;
    index_version_++;
}

void CC::init() {
    uint32_t total_nodes = graph_.getNodes('N');
    ccindex_.init(total_nodes);
    ccindex_.setElements(total_nodes);
    explored_set_.init(total_nodes);
    queries_count_ = 0;
    update_index_use_count_ = 0;
    index_version_++;
}

void CC::print() {
    for (uint32_t n = 0 ; n < graph_.getNodes('N') ; n++) {
        cout << n << " " << ccindex_[n] << "\n";
    }
    cout << "Updates: \n";
    for (uint32_t n = 0 ; n < update_index_.getElements() ; n++) {
        cout << n << ":" << (update_index_[n].index_version == index_version_ ? update_index_[n].neighbor : -1) << ":" << update_index_[n].graph_version;
        cout << "\n";
    }
    cout << "Nodes are " << graph_.getNodes('N') << endl;
}