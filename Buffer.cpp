#include "Buffer.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <assert.h>

using namespace std;

Buffer::Buffer() : curListNodes(0), maxListNodes(INITIAL_MAX_LIST_NODES) {
   buffer = new ListNode[INITIAL_MAX_LIST_NODES * sizeof(ListNode)];
    // buffer = (ListNode *)malloc(INITIAL_MAX_LIST_NODES * sizeof(ListNode));
    // assert(buffer != NULL);
    // for (uint32_t i = 0 ; i < INITIAL_MAX_LIST_NODES ; i++) {
    //     new (&buffer[i]) ListNode();
    // }
}

Buffer::~Buffer() {
   delete[] buffer;
    // for (uint32_t i = 0 ; i < maxListNodes ; i++) {
    //     buffer[i].~ListNode();
    // }
    // free(buffer);
}

/* Get a new listNode, reallocate buffer if necessary.
 * Any pointers to listNodes received prior to this function call
 * should be considered invalid and must be fetched again,
 * due to the possibility of a buffer reallocation. */
ListNodePos Buffer::allocNewNode() {
    if (curListNodes == maxListNodes) {
        maxListNodes *= 2;
       ListNode *oldBuffer = buffer;
        // buffer = (ListNode *)realloc(buffer, maxListNodes * sizeof(ListNode));
        // assert(buffer != NULL);
        // for (uint32_t i = curListNodes ; i < maxListNodes ; i++) {
        //     new (&buffer[i]) ListNode();
        // }
       buffer = new ListNode[maxListNodes];
       memcpy(buffer, oldBuffer, curListNodes * sizeof(ListNode));
       delete[] oldBuffer;
    }
    return ListNodePos(curListNodes++);
}

ListNode *Buffer::getListNode(const uint32_t &listNodePos) {
    return &buffer[listNodePos];
}

BufferFeedback Buffer::insertNeighbor(const uint32_t &firstPos, const uint32_t &neighborId, bool &skipSearch) {
    uint32_t curPos = firstPos;
    ListNode *curNode = this->getListNode(curPos);

    /* No duplicates */
    if (! skipSearch && curNode->search(neighborId)) {
        return BufferFeedback(true, curPos);
    }
    ListNodePos nextNodePos = curNode->getNextPos();

    /* Reach final listNode */
    while (nextNodePos.getExists()) {
        curPos = nextNodePos.getPos();
        curNode = this->getListNode(curPos);
        if (curNode->search(neighborId)) {
            return BufferFeedback(true, curPos);
        }
        nextNodePos = curNode->getNextPos();
    }
    skipSearch = true;

    /* Allocate new if necessary */
    if (curNode->isFull()) {
        nextNodePos = this->allocNewNode();

        curNode = this->getListNode(curPos);
        curNode->setNextPos(nextNodePos);
        curPos = nextNodePos.getPos();
        curNode = this->getListNode(curPos);
    }
    curNode->insertNeighbor(neighborId);
    return BufferFeedback(false, curPos);
}

void Buffer::print() const {
    cout << "--- Buffer ---\ncurListNodes: " << curListNodes << ", maxListNodes: " << maxListNodes << "\n" << endl;
}
