#include "Index.h"
#include <iostream>
#include <cstring>

using namespace std;

Index::Index() : curSize(0), maxSize(INITIAL_INDEX_MAX_SIZE) {
    index = new u_int32_t[INITIAL_INDEX_MAX_SIZE];
}

Index::~Index() {
    delete[] index;
}

void Index::insertNode(const u_int32_t& nodeId) {
    if (curSize == maxSize) {
        maxSize *= 2;
        u_int32_t *oldIndex = index;
        index = new u_int32_t[maxSize];
        memcpy(index, oldIndex, curSize * sizeof(u_int32_t));
        delete[] oldIndex;
    }
    index[curSize++] = -1;
}

u_int32_t Index::getListHead(const u_int32_t &nodeId) {
    return index[nodeId];
}

void Index::print() const {
    cout << "--- Index ---\ncurSize: " << curSize << "\nmaxSize: " << maxSize << endl;
    for (u_int32_t node = 0 ; node < curSize ; node++) {
        cout << index[node] << endl;
    }
}