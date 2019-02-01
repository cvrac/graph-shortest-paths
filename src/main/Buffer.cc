#include "Buffer.hh"

#include <cstring>
#include <stdlib.h>
#include <assert.h>

#include <iostream>

using namespace std;

Buffer::Buffer(const uint32_t &list_nodes) : buffer_(NULL),
    cur_list_nodes_(0), max_list_nodes_(list_nodes), total_reallocs_(0) {
    // buffer_ = new ListNode[INITIAL_MAX_LIST_NODES * sizeof(ListNode)];
//    buffer_ = (ListNode *)malloc(INITIAL_MAX_LIST_NODES * sizeof(ListNode));
    if (max_list_nodes_) {
        buffer_ = new ListNode[max_list_nodes_];
        assert(buffer_ != NULL);
    }
//    for (uint32_t i = 0 ; i < INITIAL_MAX_LIST_NODES ; i++) {
//        new (&buffer_[i]) ListNode();
//    }
}

Buffer::~Buffer() {
    delete[] buffer_;
//    for (uint32_t i = 0 ; i < max_list_nodes_ ; i++) {
//        buffer_[i].~ListNode();
//    }
//    free(buffer_);

}

void Buffer::init(const uint32_t &size) {
    assert(!max_list_nodes_);
    buffer_ = new ListNode[size];
    max_list_nodes_ = size;
    cur_list_nodes_ = 0;
}

/* Get a new list_node, reallocate buffer_ if necessary.
 * Any pointers to listNodes received prior to this function call
 * should be considered invalid and must be fetched again,
 * due to the possibility of a buffer_ reallocation. */
long Buffer::allocNewNode() {
    if (cur_list_nodes_ == max_list_nodes_) {
        max_list_nodes_ <<= 1;
        ListNode *old_buffer = buffer_;
//        buffer_ = (ListNode *)realloc(buffer_, max_list_nodes_ * sizeof(ListNode));
//        assert(buffer_ != NULL);
//        for (uint32_t i = cur_list_nodes_ ; i < max_list_nodes_ ; i++) {
//            new (&buffer_[i]) ListNode();
//        }
        buffer_ = new ListNode[max_list_nodes_];
        memcpy(buffer_, old_buffer, cur_list_nodes_ * sizeof(ListNode));
        delete[] old_buffer;
        total_reallocs_++;
    }
    return cur_list_nodes_++;
}

bool Buffer::insertNeighbor(const long &first_pos, const uint32_t &neighbor_id, const char &mode, const uint32_t &edge_version, const bool &skip_search, long *last_pos) {
    long cur_pos = first_pos;
    ListNode *cur_node = this->getListNode(cur_pos);

    /* No duplicates */
    if (! skip_search && cur_node->search(neighbor_id)) {
        return false;
    }
    long next_node_pos = cur_node->getNextPos();

    /* Reach final list_node*/
    while (! skip_search && next_node_pos != -1) {
        cur_pos = next_node_pos;
        cur_node = this->getListNode(cur_pos);
        if (cur_node->search(neighbor_id)) {
            return false;
        }
        next_node_pos = cur_node->getNextPos();
    }

    /* Allocate new if necessary */
    if (cur_node->isFull()) {
        next_node_pos = this->allocNewNode();

        cur_node = this->getListNode(cur_pos);
        cur_node->setNextPos(next_node_pos);
        cur_pos = next_node_pos;
        cur_node = this->getListNode(cur_pos);
    }
    cur_node->insertNeighbor(neighbor_id, mode, edge_version);
    *last_pos = cur_pos;
    return true;
}

void Buffer::print() const {
    cout << "--- Buffer ---\ncur_list_nodes_: " << cur_list_nodes_ << ", max_list_nodes_: " << max_list_nodes_ << "\n" << endl;
}
