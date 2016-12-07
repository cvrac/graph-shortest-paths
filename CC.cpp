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
        if (! graph_.checkMarkCCFlag(start_node, cc_flag_)) {
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
                if (graph_.checkMarkCCFlag(node, cc_flag_)) {
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
    size_index_.init(cc_id+2);  // Size index compatibility with visit_version not implemented (yet)
    size_index_.setElements(cc_id+2);
    size_index_[0] = 0; // indexing from 1
    size_index_[1] = cc_id+1;
    for (uint32_t i = 2 ; i < size_index_.getElements() ; i++) {
        size_index_[i] = 0;
    }
}

void CC::insertNewEdge(const uint32_t &source_node, const uint32_t &target_node) {
    assert(source_node < ccindex_.getElements() && target_node < ccindex_.getElements()); // Temp assert. Should always succeed according to them
    uint32_t comp1 = ccindex_[source_node];
    uint32_t comp2 = ccindex_[target_node];
    if (comp1 == comp2) {
        return;
    }
    uint32_t size1 = update_index_[comp1].getElements();
    uint32_t size2 = update_index_[comp2].getElements();

    /* Make sure they components aren't already connected.
     * If they are, they will definitely have the same number of component neighbors,
     * so skip search otherwise */

   // cout << size1 << " Vs " << size2 << "\n";
    if (size1 == size2 && (size_index_[size1+1] == 1 || update_index_[comp1].search(comp2))) {
        //cout << "\tsame " << (size_index_[size1+1] == 1) << "\n";
        return;
    }

    size_index_[size1+1]--;
    size_index_[size2+1]--;
    size_index_[size1+size2+2]++;

    update_index_[comp1].pushBatch(update_index_[comp2].getArray(), size2);
    update_index_[comp1].enstack(comp2);
    for (uint32_t n = 0 ; n < size1 ; n++) {
        update_index_[update_index_[comp1][n]].pushBatch(update_index_[comp2].getArray(), size2);
        update_index_[update_index_[comp1][n]].enstack(comp2);
    }

    update_index_[comp2].pushBatch(update_index_[comp1].getArray(), size1);
    update_index_[comp2].enstack(comp1);
    for (uint32_t n = 0 ; n < size2 ; n++) {
        update_index_[update_index_[comp2][n]].pushBatch(update_index_[comp1].getArray(), size1);
        update_index_[update_index_[comp2][n]].enstack(comp1);
    }
/*
    uint32_t min = ccindex_[source_node];
    uint32_t max = ccindex_[target_node];
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
    update_index_[min].visit_version_ = visit_version_;*/
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
    uint32_t size1 = update_index_[comp1].getElements();
    uint32_t size2 = update_index_[comp2].getElements();

    //cout << size1 << " Vs " << size2 << "\n";
    if (size1 == size2 && (size_index_[size1+1] == 1 || update_index_[comp1].search(comp2))) {
        //cout << "\tsame " << (size_index_[size1+1] == 1) << "\n";
        return true;
    }
    return false;/*

    uint32_t min = ccindex_[source_node];
    uint32_t max = ccindex_[target_node];
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
    return false;*/
}

void CC::reset() {
    uint32_t total_nodes = graph_.getNodes();
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
    cout << "\n*** Sizes\n";
    for (uint32_t i = 1 ; i < size_index_.getElements() ; i++) {
        if (size_index_[i]) {
            cout << "size_index_[" << i << "] = " << size_index_[i] << "\n";
        }
    }
    cout << "Nodes are " << graph_.getNodes() << endl;
}