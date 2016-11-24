#include "NodeIndex.hpp"

#include <cstring>
#include <stdlib.h>
#include <assert.h>

#include <iostream>

using namespace std;

NodeIndex::NodeIndex() : index_(new ListHead[INITIAL_INDEX_MAX_SIZE]), cur_size_(0),
    max_size_(INITIAL_INDEX_MAX_SIZE), total_reallocs_(0) {
//    index_ = (ListHead *)malloc(INITIAL_INDEX_MAX_SIZE * sizeof(ListHead));
    assert(index_ != NULL);
//    for (uint32_t i = 0 ; i < INITIAL_INDEX_MAX_SIZE ; i++) {
//        new (&index_[i]) ListHead();
//    }
    index_->total_neighbors = 0;
}

NodeIndex::~NodeIndex() {
    delete[] index_;
//    for (uint32_t i = 0 ; i < max_size_ ; i++) {
//        index_[i].~ListHead();
//    }
//    free(index_);
}


void NodeIndex::insertNode(const uint32_t &node_id) {
    if (max_size_ <= node_id) {
        // uint32_t oldMaxSize = max_size_;
        while (max_size_ <= node_id) {
            max_size_ *= 2;
        }
        ListHead *oldNodeIndex = index_;
        index_ = new ListHead[max_size_];
        memcpy(index_, oldNodeIndex, cur_size_ * sizeof(ListHead));
//        index_ = (ListHead *)realloc(index_, max_size_ * sizeof(ListHead));
//        assert(index_ != NULL);
//        for (uint32_t i = oldMaxSize ; i < max_size_ ; i++) {
//            new (&index_[i]) ListHead();
//        }
        delete[] oldNodeIndex;
        total_reallocs_++;
        cur_size_ = node_id + 1;
    }
    else if (cur_size_ <= node_id){
        cur_size_ = node_id + 1;
    }
}

void NodeIndex::insertNeighborInHash(const uint32_t &node_id, const uint32_t &neighbor_id) {
    if (index_[node_id].neighbors_hash_ == NULL) {
        index_[node_id].neighbors_hash_ = new HashTable<uint32_t>(HASH_SIZE);
    }
    index_[node_id].neighbors_hash_->insert(neighbor_id);
}

bool NodeIndex::searchNeighborInHash(const uint32_t &node_id, const uint32_t &neighbor_id) {
    if (index_[node_id].neighbors_hash_ == NULL) {
        return false;
    }
    return index_[node_id].neighbors_hash_->search(neighbor_id);
}

bool NodeIndex::searchInsertHash(const uint32_t &node_id, const uint32_t &neighbor_id) {
    if (index_[node_id].neighbors_hash_ == NULL) {
        index_[node_id].neighbors_hash_ = new HashTable<uint32_t>(HASH_SIZE);
        index_[node_id].neighbors_hash_->insert(neighbor_id);
        return true;
    }
    return index_[node_id].neighbors_hash_->searchInsert(neighbor_id);
}

uint32_t NodeIndex::getHashNeighbors(const uint32_t &source, const uint32_t &target) const {
    if (index_[source].neighbors_hash_ == NULL) {
        return 0;
    }
    return index_[source].neighbors_hash_->getBucketCount(target);
}

uint32_t NodeIndex::getAverageNeighbors() {
    long long sum = 0;
    for (uint32_t node = 0; node < cur_size_; node++) {
        sum += index_[node].total_neighbors;
    }
    return (uint32_t) (sum / cur_size_);
}

void NodeIndex::print() const {
    cout << "--- NodeIndex ---\ncur_size_: " << cur_size_ << ", max_size_: " << max_size_ << endl;
    for (uint32_t node = 0; node < cur_size_; node++) {
        cout << node << " with " << index_[node].total_neighbors << " neighbors: ";
        cout << "\nFirst pos is " << index_[node].pos << "Last pos is " << index_[node].last_pos << endl;
        }
    cout << endl;
}

void NodeIndex::printNeighborsHash(const uint32_t &node_id) const {
    if (index_[node_id].neighbors_hash_ != NULL) {
        index_[node_id].neighbors_hash_->print();
    }
}

void NodeIndex::deleteNeigborsHash() {
    for (uint32_t node = 0; node < cur_size_; node++) {
        if (index_[node].neighbors_hash_ != NULL) {
            delete index_[node].neighbors_hash_;
        }
    }
}
