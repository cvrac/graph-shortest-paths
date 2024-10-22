#include "ListNode.hh"

#include <iostream>

using namespace std;

void ListNode::insertNeighbor(const uint32_t &neighbor_id, const char &mode, const uint32_t &edge_version) {
    if (this->isFull()) {
        return;
    }
    neighbor_[cur_neighbors_++] = neighbor_id;
    if (mode != 'S') {
        edge_version_[cur_neighbors_-1] = edge_version;
    }
}

bool ListNode::search(const uint32_t &target_id) {
    for (uint32_t n = 0 ; n < cur_neighbors_ ; n++) {
        if (neighbor_[n] == target_id) {
            return true;
        }
    }
    return false;
}

void ListNode::print() const {
    cout << "\t--- ListNode ---\n\tcur_neighbors_: " << cur_neighbors_ << ", maxNeighbors: " << MAX_NEIGHBORS
         << ", nextListNode: " << next_pos_;
    cout << "\t";
    for (uint32_t n = 0; n < cur_neighbors_ ; n++) {
        cout << neighbor_[n] << " ";
    }
    cout << "\n" << endl;
}
