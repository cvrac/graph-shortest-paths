#include "Index.h"

#include <cstring>
#include <stdlib.h>
#include <assert.h>

#include <iostream>

using namespace std;

Index::Index() : curSize(0), maxSize(INITIAL_INDEX_MAX_SIZE), totalReallocs(0) {
    index = new ListHead[INITIAL_INDEX_MAX_SIZE];
//    index = (ListHead *)malloc(INITIAL_INDEX_MAX_SIZE * sizeof(ListHead));
    assert(index != NULL);
//    for (uint32_t i = 0 ; i < INITIAL_INDEX_MAX_SIZE ; i++) {
//        new (&index[i]) ListHead();
//    }
    index->totalNeighbors = 0;
}

Index::~Index() {
    delete[] index;
//    for (uint32_t i = 0 ; i < maxSize ; i++) {
//        index[i].~ListHead();
//    }
//    free(index);
}


void Index::insertNode(const uint32_t &nodeId) {
    if (maxSize <= nodeId) {
        uint32_t oldMaxSize = maxSize;
        while (maxSize <= nodeId) {
            maxSize *= 2;
        }
        ListHead *oldIndex = index;
        index = new ListHead[maxSize];
        memcpy(index, oldIndex, curSize * sizeof(ListHead));
//        index = (ListHead *)realloc(index, maxSize * sizeof(ListHead));
//        assert(index != NULL);
//        for (uint32_t i = oldMaxSize ; i < maxSize ; i++) {
//            new (&index[i]) ListHead();
//        }
        delete[] oldIndex;
        totalReallocs++;
        curSize = nodeId + 1;
    }
    else if (curSize <= nodeId){
        curSize = nodeId + 1;
    }
}

uint32_t Index::getAverageNeighbors() {
    long long sum = 0;
    for (uint32_t node = 0; node < curSize; node++) {
        sum += index[node].totalNeighbors;
    }
    return (uint32_t) (sum / curSize);
}

void Index::print() const {
    cout << "--- Index ---\ncurSize: " << curSize << ", maxSize: " << maxSize << endl;
    for (uint32_t node = 0; node < curSize; node++) {
        cout << node << " with " << index[node].totalNeighbors << " neighbors: ";
        index[node].pos.print();
        if (index[node].pos.getExists()) {
            cout << "Last pos is " << index[node].lastPos << endl;
        }
    }
    cout << endl;
}

