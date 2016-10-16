#include "Buffer.h"
#include <iostream>
#include <cstring>

using namespace std;

Buffer::Buffer() : curListNodes(0), maxListNodes(INITIAL_MAX_LIST_NODES) {
    buffer = new ListNode[INITIAL_MAX_LIST_NODES * sizeof(ListNode)];
}

Buffer::~Buffer() {
    delete[] buffer;
}

uint32_t Buffer::allocNewNode() {
    if (curListNodes == maxListNodes) {
        maxListNodes *= 2;
        ListNode *oldBuffer = buffer;
        buffer = new ListNode[maxListNodes];
        memcpy(buffer, oldBuffer, curListNodes * sizeof(ListNode));
        delete[] oldBuffer;
    }
    return curListNodes++;
}

ListNode *Buffer::getListNode(const uint32_t &listNodePos) {
    return &buffer[listNodePos];
}

void Buffer::insertNeighbor(const uint32_t &listNodePos, const uint32_t &neighborId) {
    ListNode *listNode = this->getListNode(listNodePos);
    ListNodePos nextNodePos = listNode->getNextListNodePos();
    while (nextNodePos.getExists()) {
        uint32_t nextPos = nextNodePos.getListNodePos();
        listNode = this->getListNode(nextPos);
        nextNodePos = listNode->getNextListNodePos();
    }

    if (listNode->isFull()) {
        uint32_t nextPos = this->allocNewNode();
        ListNodePos nextListNodePos(nextPos);
        listNode->setNextListNodePos(nextListNodePos);
        listNode = this->getListNode(nextPos);
    }

    listNode->insertNeighbor(neighborId);
}

void Buffer::print() const {
    cout << "--- Buffer ---\ncurListNodes: " << curListNodes << ", maxListNodes: " << maxListNodes << "\n" << endl;
}