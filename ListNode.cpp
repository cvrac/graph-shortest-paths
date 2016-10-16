#include "ListNode.h"
#include <iostream>

using namespace std;

ListNode::ListNode() : curNeighbors(0) {}

void ListNode::insertNeighbor(const uint32_t &neighborId) {
    if (this->isFull()) {
        return;
    }
    neighbor[curNeighbors++] = neighborId;
}

void ListNode::print() const {
    cout << "\t--- ListNode ---\n\tcurNeighbors: " << curNeighbors << ", maxNeighbors: " << MAX_NEIGHBORS
         << ", nextListNode: ";
    nextListNodePos.print();
    cout << "\t";
    for (uint32_t n = 0; n < curNeighbors ; n++) {
        cout << neighbor[n] << " ";
    }
    cout << "\n" << endl;
}

