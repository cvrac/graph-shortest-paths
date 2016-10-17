#include "Index.h"
#include <iostream>
#include <cstring>

using namespace std;

Index::Index() : curSize(0), maxSize(INITIAL_INDEX_MAX_SIZE) {
    index = new ListNodePos[INITIAL_INDEX_MAX_SIZE];
}

Index::~Index() {
    delete[] index;
}

/* Insert node only if it is the direct successor of the last one */
void Index::insertNode(const uint32_t &nodeId) {
    if (nodeId != curSize){
        return;
    }
    if (curSize == maxSize) {
        maxSize *= 2;
        ListNodePos *oldIndex = index;
        index = new ListNodePos[maxSize];
        memcpy(index, oldIndex, curSize * sizeof(ListNodePos));
        delete[] oldIndex;
    }
    curSize++;
}

void Index::setListHead(const uint32_t &nodeId, const ListNodePos &head) {
    index[nodeId] = head;
}

void Index::print() const {
    cout << "--- Index ---\ncurSize: " << curSize << ", maxSize: " << maxSize << endl;
    for (uint32_t node = 0; node < curSize; node++) {
        cout << node << ": ";
        index[node].print();
    }
    cout << endl;
}

