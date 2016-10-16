#include "Buffer.h"

using namespace std;

Buffer::Buffer() : curListNodes(0), maxListNodes(INITIAL_MAX_LIST_NODES) {
    buffer = new ListNode[INITIAL_MAX_LIST_NODES * sizeof(ListNode)];
}

Buffer::~Buffer() {
    delete[] buffer;
}

u_int32_t Buffer::allocNewNode() {
    if (curListNodes == maxListNodes) {
        maxListNodes *= 2;
        ListNode *oldBuffer = buffer;
        buffer = new ListNode[maxListNodes];
        memcpy(buffer, oldBuffer, curListNodes * sizeof(ListNode));
        delete[] oldBuffer;
    }
    return curListNodes++;
}

ListNode *Buffer::getListNode(const u_int32_t& listNode) {
    return &buffer[listNode];
}