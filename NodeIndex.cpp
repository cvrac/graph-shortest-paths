#include "NodeIndex.hpp"

#include <cstring>
#include <stdlib.h>
#include <assert.h>

#include <iostream>

using namespace std;

NodeIndex::NodeIndex(const uint32_t &size) : index_(NULL), cur_size_(0),
    max_size_(size), total_reallocs_(0) {
    if (size) {
        index_ = new ListHead[size];
        assert(index_ != NULL);
    }
//    index_ = (ListHead *)malloc(INITIAL_INDEX_MAX_SIZE * sizeof(ListHead));
//    for (uint32_t i = 0 ; i < INITIAL_INDEX_MAX_SIZE ; i++) {
//        new (&index_[i]) ListHead();
//    }
}

NodeIndex::~NodeIndex() {
    delete[] index_;
//    for (uint32_t i = 0 ; i < max_size_ ; i++) {
//        index_[i].~ListHead();
//    }
//    free(index_);
}

void NodeIndex::init(const uint32_t &size) {
    assert(!max_size_ );
    index_ = new ListHead[size];
    max_size_ = size;
    cur_size_ = max_size_;
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

void NodeIndex::insertNeighborInHash(const uint32_t &node_id, const uint32_t &neighbor_id, const char &mode) {
    if (index_[node_id].neighbors_hash_ == NULL) {
        index_[node_id].neighbors_hash_ = new HashTable<uint32_t>((mode == 'S' ? HASH_SIZE_SCC : HASH_SIZE));
    }
    index_[node_id].neighbors_hash_->insert(neighbor_id);
}

bool NodeIndex::searchNeighborInHash(const uint32_t &node_id, const uint32_t &neighbor_id) {
    if (index_[node_id].neighbors_hash_ == NULL) {
        return false;
    }
    return index_[node_id].neighbors_hash_->search(neighbor_id);
}

bool NodeIndex::searchInsertHash(const uint32_t &node_id, const uint32_t &neighbor_id, const char &mode) {
    if (index_[node_id].neighbors_hash_ == NULL) {
        index_[node_id].neighbors_hash_ = new HashTable<uint32_t>((mode == 'S' ? HASH_SIZE_SCC : HASH_SIZE));
        index_[node_id].neighbors_hash_->insert(neighbor_id);
        return true;
    }
    return index_[node_id].neighbors_hash_->searchInsert(neighbor_id);
}

uint32_t NodeIndex::getAverageNeighbors() {
    long long sum = 0;
    for (uint32_t node = 0; node < cur_size_; node++) {
        sum += index_[node].total_neighbors;
    }
    return (uint32_t) (sum / cur_size_);
}

/* Return false if flags are the same, otherwise set and return true */
bool NodeIndex::checkSetListHeadVisitedVersion(const uint32_t &node_id, const unsigned long long &visit_version) {
    if (index_[node_id].visit_version_ == visit_version) {
        return false;
    }
    index_[node_id].visit_version_ = visit_version;
    return true;
}

bool NodeIndex::checkSetListHeadCCFlag(const uint32_t &node_id, const bool &cc_flag) {
    if (index_[node_id].cc_flag_ == cc_flag) {
        return false;
    }
    index_[node_id].cc_flag_ = cc_flag;
    return true;
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
