#include <iostream>
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
    this->insertNode(min);
    this->insertNode(max);
}

void Graph::insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId) {
    this->insertNodes(sourceNodeId, targetNodeId);
    this->insertEdge(sourceNodeId, targetNodeId, outerIndex, outerBuffer);
    this->insertEdge(targetNodeId, sourceNodeId, innerIndex, innerBuffer);
}

void Graph::insertEdge(const uint32_t &sourceNodeId, const uint32_t &targetNodeId, Index &index, Buffer &buffer) {
    ListNodePos firstPos = index.getListHead(sourceNodeId);
    if (! firstPos.getExists()) {
        firstPos = buffer.allocNewNode();
        index.setListHead(sourceNodeId, firstPos);
    }
    buffer.insertNeighbor(firstPos.getPos(), targetNodeId);
}

void Graph::print() {
    cout << "*** OUTER ***\n";
    this->print(outerIndex, outerBuffer);
    cout << "\n*** INNER ***\n";
    this->print(innerIndex, innerBuffer);
}

void Graph::print(Index &index, Buffer &buffer)  {
    buffer.print();
    index.print();
    for (uint32_t nodeId = 0 ; nodeId < index.getCurSize() ; nodeId++) {
        ListNodePos listNodePos = index.getListHead(nodeId);
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