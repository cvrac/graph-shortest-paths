#include <iostream>
#include <cstring>
#include "Graph.h"
#include "LinkedList.h"

using namespace std;

void Graph::insertNode(const uint32_t nodeId) {
    outerIndex.insertNode(nodeId);
    innerIndex.insertNode(nodeId);
}

/* Insert nodes if they don't already exist */
void Graph::insertNodes(const uint32_t &sourceNodeId, const uint32_t &targetNodeId) {
    uint32_t min = sourceNodeId;
    uint32_t max = targetNodeId;
    if (targetNodeId < min) {
        min = targetNodeId;
        max = sourceNodeId;
    }
    this->insertNode(max);
    this->insertNode(min);
}

void Graph::insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId) {
    this->insertNodes(sourceNodeId, targetNodeId);
    this->insertEdge(sourceNodeId, targetNodeId, outerIndex, outerBuffer);
    this->insertEdge(targetNodeId, sourceNodeId, innerIndex, innerBuffer);
}

void Graph::insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId, Index &index, Buffer &buffer) {
    ListNodePos firstPos = index.getListHead(sourceNodeId).pos;
    if (! firstPos.getExists()) {
        firstPos = buffer.allocNewNode();
        index.setListHeadPos(sourceNodeId, firstPos);
    }
    if (buffer.insertNeighbor(firstPos.getPos(), targetNodeId)) {
        index.setListHeadNeighbors(sourceNodeId, index.getListHeadNeighbors(sourceNodeId) + 1);
    }
}

NodeArray *Graph::getNeighbors(const uint32_t &nodeId, char& direction) {
    Index *index;
    Buffer *buffer;
    if (direction == 'F') {
        index = &outerIndex;
        buffer = &outerBuffer;
    }
    else if (direction == 'B') {
        index = &innerIndex;
        buffer = &innerBuffer;
    }
    else {
        return NULL;
    }
    return this->getNeighbors(nodeId, *index, *buffer);
}

/* Caller should free after use */
NodeArray *Graph::getNeighbors(const uint32_t &nodeId, Index &index, Buffer &buffer) {
    NodeArray *nodeArray = new NodeArray;
    ListHead listHead = index.getListHead(nodeId);
    nodeArray->array = new uint32_t[listHead.totalNeighbors];
    nodeArray->size = listHead.totalNeighbors;

    uint32_t curNeighbor = 0;
    ListNodePos listNodePos = listHead.pos;
    if (listNodePos.getExists()) {
        uint32_t pos = listNodePos.getPos();
        do {
            ListNode *listNode = buffer.getListNode(pos);
            uint32_t neighborsToAdd = listNode->getNeighborNumber();
            memcpy(&nodeArray->array[curNeighbor], listNode->getNeighborArray(), neighborsToAdd * sizeof(uint32_t));
            curNeighbor += neighborsToAdd;

            listNodePos = listNode->getNextPos();
            if (! listNodePos.getExists()) {
                break;
            }
            pos = listNodePos.getPos();
        } while (1);
    }
    return nodeArray;
}

void Graph::printAll() {
    cout << "*** OUTER ***\n";
    this->printAll(outerIndex, outerBuffer);
    cout << "\n*** INNER ***\n";
    this->printAll(innerIndex, innerBuffer);
}

void Graph::printAll(Index &index, Buffer &buffer)  {
    buffer.print();
    index.print();
    for (uint32_t nodeId = 0 ; nodeId < index.getCurSize() ; nodeId++) {
        ListNodePos listNodePos = index.getListHead(nodeId).pos;
        if (listNodePos.getExists()) {
            cout << "---Node " << nodeId << " ListNodes --- " << endl;
            uint32_t pos = listNodePos.getPos();
            do {
                ListNode *listNode = buffer.getListNode(pos);
                listNode->print();
                listNodePos = listNode->getNextPos();
                if (! listNodePos.getExists()) {
                    break;
                }
                pos = listNodePos.getPos();
            } while (1);
        }
    }
}

NodeArray::~NodeArray() {
    if (array != NULL) {
        delete[] array;
    }
}

void Graph::print() {
    cout << "*** OUTER ***\n";
    this->print(outerIndex, outerBuffer);
    cout << "\n*** INNER ***\n";
    this->print(innerIndex, innerBuffer);
}

void Graph::print(Index &index, Buffer &buffer) {
    for (uint32_t node = 0 ; node < index.getCurSize() ; node++) {
        NodeArray *neighbors = this->getNeighbors(node, index, buffer);
        cout << "Node " << node << " has " << (neighbors == NULL ? 0 : neighbors->size) << " neighbors:\n";
        if (neighbors != NULL) {
            neighbors->print();
            delete neighbors;
        }
        cout << "\n";
    }
    cout << endl;
}

void NodeArray::print() {
    //cout << "--- NodeArray ---\n" << "size: " << size << endl;
    for (int n = 0 ; n < size ; n++) {
        cout << array[n] << " ";
    }
    cout << endl;
}