#include "Graph.h"
#include <iostream>

using namespace std;

void Graph::insertNode(const int32_t nodeId) {
    outerIndex.insertNode(nodeId);
    innerIndex.insertNode(nodeId);
}

void Graph::insertEdge(const int32_t &sourceNodeId, const int32_t &targetNodeId) {
    if (sourceNodeId == outerIndex.getCurSize()) {
        outerIndex.insertNode(sourceNodeId);
    }
    if (targetNodeId == innerIndex.getCurSize()) {
        innerIndex.insertNode(targetNodeId);
    }

    uint32_t sourceListNodePos;
    ListNodePos sourceNodeOffset = outerIndex.getListHead(sourceNodeId);
    if (! sourceNodeOffset.getExists()) {//cout << "first edge" << endl;
        sourceListNodePos = outerBuffer.allocNewNode(); //cout << "sourceListNodePos " << sourceListNodePos << endl;
        sourceNodeOffset.setListNodePos(sourceListNodePos);
        sourceNodeOffset.setExists(true);
        outerIndex.setListHead(sourceNodeId, sourceNodeOffset);
    }
    else {
        sourceListNodePos = sourceNodeOffset.getListNodePos();
    }

    outerBuffer.insertNeighbor(sourceListNodePos, targetNodeId);
}

void Graph::print()  {
    outerBuffer.print();
    outerIndex.print();
    for (int32_t nodeId = 0 ; nodeId < outerIndex.getCurSize() ; nodeId++) {
        ListNodePos listNodePos = outerIndex.getListHead(nodeId);
        if (listNodePos.getExists()) {
            cout << "---Node " << nodeId << " ListNodes --- " << endl;
            int32_t pos = listNodePos.getListNodePos();
            do {
                ListNode *listNode = outerBuffer.getListNode(pos);
                listNode->print();
                listNodePos = listNode->getNextListNodePos();
                if (! listNodePos.getExists()) {
                    break;
                }
                pos = listNodePos.getListNodePos();
            } while (1);
        }
    }
}

