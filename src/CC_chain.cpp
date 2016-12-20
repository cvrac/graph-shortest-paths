#include "CC.hpp"

#include <assert.h>

#include <iostream>

using namespace std;

uint32_t count = 0;


CC::~CC() {}

void CC::estimateConnectedComponents() {
    this->reset();
    uint32_t total_nodes = graph_.getNodes('N');
    assert(total_nodes);

    bool first = true;
    uint32_t cc_id = 0;
    for (uint32_t start_node = 0 ; start_node < total_nodes ; start_node++) {
        if (! graph_.checkMarkCCFlag(start_node, cc_flag_, 'N')) {
            continue;
        }
        if (!first) {
            cc_id++;
        }
        ccindex_[start_node] = cc_id;
        frontier_.enstack(start_node);
        while (! frontier_.isEmpty()) {
            uint32_t node = frontier_.popBack();
            Garray<uint32_t > &neighbors = graph_.getNeighbors(node, 'A');
            for (int i = 0; i < neighbors.getElements(); i++) {
                node = neighbors[i];
                if (graph_.checkMarkCCFlag(node, cc_flag_, 'N')) {
                    frontier_.enstack(node);
                    ccindex_[node] = cc_id;
                }
            }
        }
        if (first) {
            first = false;
        }
    }
    //if (visit_version_ == 1) {   // Omitting new/deletes with versioning barely helps
        update_index_.init(cc_id+1);
        update_index_.setElements(cc_id+1);
    //  }
}

void CC::insertNewEdge(const uint32_t &source_node, const uint32_t &target_node) {
    assert(source_node < ccindex_.getElements() && target_node < ccindex_.getElements()); // Temp assert. If failure, implement new node addition
    uint32_t min = findNodeConnectedComponentID(source_node);
    uint32_t max = findNodeConnectedComponentID(target_node);
    if (min == max) {
        return;
    }
    if (min > max) {
        uint32_t temp = min;
        min = max;
        max = temp;
    }
    while (update_index_[min].visit_version_ == visit_version_) {
        if (update_index_[min].neighbor_ == max) {
            return;
        } else if (update_index_[min].neighbor_ < max) {
            min = update_index_[min].neighbor_;
        }
        else {
            uint32_t temp = max;
            max = update_index_[min].neighbor_;
            min = temp;
        }
    }
    update_index_[min].neighbor_ = max;
    update_index_[min].visit_version_ = visit_version_;
}

bool CC::sameConnectedComponent(const uint32_t &source_node, const uint32_t &target_node) {
    count++;
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
    while (update_index_[min].visit_version_ == visit_version_) {
        if (update_index_[min].neighbor_ == max) {
            return true;
        } else if (update_index_[min].neighbor_ < max) {
            min = update_index_[min].neighbor_;
        }
        else {
            uint32_t temp = max;
            max = update_index_[min].neighbor_;
            min = temp;
        }
    }
    return false;
}

void CC::reset() {
    uint32_t total_nodes = graph_.getNodes('N');
    ccindex_.init(total_nodes);
    ccindex_.setElements(total_nodes);
    queries_count_ = 0;
    update_index_use_count_ = 0;
    visit_version_++;
    if (cc_flag_) {
        cc_flag_ = false;
    } else {
        cc_flag_ = true;
    }
}

void CC::print() {
//    for (uint32_t n = 0 ; n < graph_.getNodes() ; n++) {
    //    cout << n << " " << ccindex_[n] << "\n";
  //  }
   // cout << "Updates: \n";
   // for (uint32_t n = 0 ; n < update_index_.getElements() ; n++) {
    //    cout << n << ":"; update_index_[n].print();//visit_version_ == visit_version_ ? update_index_[n].neighbor_ : -1);
     //   cout << "\n";
   // }
    cout << "Nodes are " << graph_.getNodes('N') << endl;
}