#include "ListNode.h"

#include <iostream>

using namespace std;

void ListNode::insertNeighbor(const uint32_t &neighborId) {
    if (this->isFull()) {
        return;
    }
    neighbor[curNeighbors++] = neighborId;
}

bool ListNode::search(const uint32_t &targetId) {
    for (uint32_t n = 0 ; n < curNeighbors ; n++) {
        if (neighbor[n] == targetId) {
            return true;
        }
    }
    return false;
}

void ListNode::print() const {
    cout << "\t--- ListNode ---\n\tcurNeighbors: " << curNeighbors << ", maxNeighbors: " << MAX_NEIGHBORS
         << ", nextListNode: ";
    nextPos.print();
    cout << "\t";
    for (uint32_t n = 0; n < curNeighbors ; n++) {
        cout << neighbor[n] << " ";
    }
    cout << "\n" << endl;
}

