#include "Buffer.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <assert.h>

using namespace std;

Buffer::Buffer() : curListNodes(0), maxListNodes(INITIAL_MAX_LIST_NODES) {
    buffer = new ListNode[INITIAL_MAX_LIST_NODES * sizeof(ListNode)];
//    buffer = (ListNode *)malloc(INITIAL_MAX_LIST_NODES * sizeof(ListNode));
    assert(buffer != NULL);
}

Buffer::~Buffer() {
    delete[] buffer;
//    free(buffer);
}

/* Get a new listNode, reallocate buffer if necessary.
 * Any pointers to listNodes received prior to this function call
 * should be considered invalid and must be fetched again,
 * due to the possibility of a buffer reallocation. */
ListNodePos Buffer::allocNewNode() {
    if (curListNodes == maxListNodes) {
        maxListNodes *= 2;
        ListNode *oldBuffer = buffer;
//        buffer = (ListNode *)realloc(buffer, maxListNodes * sizeof(ListNode));
        assert(buffer != NULL);
        buffer = new ListNode[maxListNodes];
        memcpy(buffer, oldBuffer, curListNodes * sizeof(ListNode));
        delete[] oldBuffer;
    }
    return ListNodePos(curListNodes++);
}

ListNode *Buffer::getListNode(const uint32_t &listNodePos) {
    return &buffer[listNodePos];
}

bool Buffer::insertNeighbor(const uint32_t &firstPos, const uint32_t &neighborId) {
    uint32_t curPos = firstPos;
    ListNode *curNode = this->getListNode(curPos);

    /* No duplicates */
    if (curNode->search(neighborId)) {
        return false;
    }
    ListNodePos nextNodePos = curNode->getNextPos();

    /* Reach final listNode */
    while (nextNodePos.getExists()) {
        curPos = nextNodePos.getPos();
        curNode = this->getListNode(curPos);
        if (curNode->search(neighborId)) {
            return false;
        }
        nextNodePos = curNode->getNextPos();
    }

    /* Allocate new if necessary */
    if (curNode->isFull()) {
        nextNodePos = this->allocNewNode();

        curNode = this->getListNode(curPos);
        curNode->setNextPos(nextNodePos);
        curNode = this->getListNode(nextNodePos.getPos());
    }
    curNode->insertNeighbor(neighborId);
    return true;
}

void Buffer::print() const {
    cout << "--- Buffer ---\ncurListNodes: " << curListNodes << ", maxListNodes: " << maxListNodes << "\n" << endl;
}