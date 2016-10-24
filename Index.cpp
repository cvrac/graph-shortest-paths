#include "Index.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <assert.h>

using namespace std;

Index::Index() : curSize(0), maxSize(INITIAL_INDEX_MAX_SIZE) {
    index = new ListHead[INITIAL_INDEX_MAX_SIZE];
//    index = (ListHead *)malloc(INITIAL_INDEX_MAX_SIZE * sizeof(ListHead));
    assert(index != NULL);
    index->totalNeighbors = 0;
}

Index::~Index() {
    delete[] index;
//    free(index);
}


/* Insert node only if it is the direct successor of the last one */
void Index::insertNode(const uint32_t &nodeId) {
    if (nodeId != curSize){
        return;
    }
    if (curSize == maxSize) {
        maxSize *= 2;
        ListHead *oldIndex = index;
        index = new ListHead[maxSize];
        memcpy(index, oldIndex, curSize * sizeof(ListHead));
//        index = (ListHead *)realloc(index, maxSize * sizeof(ListHead));
        assert(index != NULL);
        delete[] oldIndex;
    }
    curSize++;
}

void Index::print() const {
    cout << "--- Index ---\ncurSize: " << curSize << ", maxSize: " << maxSize << endl;
    for (uint32_t node = 0; node < curSize; node++) {
        cout << node << " with " << index[node].totalNeighbors << " neighbors: ";
        index[node].pos.print();
    }
    cout << endl;
}

