#include "Graph.hpp"

#include <cstring>
#include <time.h>

#include <iostream>

#include "Queue.hpp"

using namespace std;

void Graph::insertNode(const uint32_t node_id) {
    outer_index_.insertNode(node_id);
    inner_index_.insertNode(node_id);
}

void Graph::insertNodes(const uint32_t &source_node_id, const uint32_t &target_node_id) {
    uint32_t min = source_node_id;
    uint32_t max = target_node_id;
    if (target_node_id < min) {
        min = target_node_id;
        max = source_node_id;
    }
    this->insertNode(max);
    this->insertNode(min);
}

void Graph::insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id) {
    this->insertNodes(source_node_id, target_node_id);
    // clock_t start = clock();
    const uint32_t *node1 = &source_node_id;
    const uint32_t *node2 = &target_node_id;
    Index *index = &outer_index_;
    Buffer *buffer = &outer_buffer_;
    bool skip_search = false;

    if (outer_index_.getListHead(*node1).total_neighbors > inner_index_.getListHead(*node2).total_neighbors) {
        this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer);
    }
    if (this->insertEdge(*node1, *node2, index, buffer, &skip_search)) {
        this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer);
        this->insertEdge(*node1, *node2, index, buffer, &skip_search);
    }
    // clock_t end = clock();
    // cout << "edge insertion took " << static_cast<double>((end - start) / CLOCKS_PER_SEC) << endl;
}

bool Graph::insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, Index *index, Buffer *buffer, bool *skip_search) {
    ListNodePos first_pos = index->getListHead(source_node_id).pos;
    if (! first_pos.exists) {
        first_pos = buffer->allocNewNode();
        index->setListHeadPos(source_node_id, first_pos);
        index->setListHeadLast(source_node_id, first_pos.getPos());
    }
    uint32_t pos;
    if (! skip_search) {
        pos = first_pos.pos;
    } else {
        pos = index->getListHead(source_node_id).last_pos;
    }
    BufferFeedback feedback = buffer->insertNeighbor(pos, target_node_id, skip_search);
    if (feedback.edge_exists) {
        return false;
    }
    index->setListHeadNeighbors(source_node_id, index->getListHeadNeighbors(source_node_id) + 1);
    index->setListHeadLast(source_node_id, feedback.last_pos);
    //cout << index.getListHeadNeighbors(source_node_id) << endl;
    return true;
}

void Graph::toggleDirection(const uint32_t &source_node_id, const uint32_t &target_node_id, const uint32_t **node1, const uint32_t **node2, Index **index, Buffer **buffer) {
    if (**node1 == source_node_id) {
        *node1 = &target_node_id;
        *node2 = &source_node_id;
        *index = &inner_index_;
        *buffer = &inner_buffer_;
    }
    else {
        *node1 = &source_node_id;
        *node2 = &target_node_id;
        *index = &outer_index_;
        *buffer = &outer_buffer_;
    }
}

NodeArray *Graph::getNeighbors(const uint32_t &node_id, const char& direction) {
    Index *index;
    Buffer *buffer;
    if (direction == 'F') {
        index = &outer_index_;
        buffer = &outer_buffer_;
    }
    else if (direction == 'B') {
        index = &inner_index_;
        buffer = &inner_buffer_;
    }
    else {
        return NULL;
    }
    return this->getNeighbors(node_id, *index, *buffer);
}

/* Caller should free after use */
NodeArray *Graph::getNeighbors(const uint32_t &node_id, const Index &index, const Buffer &buffer) {
    NodeArray *node_array = new NodeArray;
    ListHead list_head = index.getListHead(node_id);
    node_array->array = new uint32_t[list_head.total_neighbors];
    node_array->size = list_head.total_neighbors;

    uint32_t cur_neighbor = 0;
    ListNodePos list_node_pos = list_head.pos;
    if (list_node_pos.exists) {
        uint32_t pos = list_node_pos.pos;
        do {
            ListNode list_node = buffer.getListNode(pos);
            uint32_t neighbors_to_add = list_node.getNeighborNumber();
            memcpy(&node_array->array[cur_neighbor], list_node.getNeighborArray(), neighbors_to_add * sizeof(uint32_t));
            cur_neighbor += neighbors_to_add;

            list_node_pos = list_node.getNextPos();
            if (! list_node_pos.exists) {
                break;
            }
            pos = list_node_pos.pos;
        } while (1);
    }
    return node_array;
}

uint32_t Graph::getStatistics() {
    cout << "Nodes: " << this->getNodes() << "\nAverage outer edges: " <<
    outer_index_.getAverageNeighbors() << "\nAverage inner edges: " <<
    inner_index_.getAverageNeighbors() << "\nBuffer reallocs: " <<
    outer_buffer_.getTotalReallocs() + inner_buffer_.getTotalReallocs() << "\nIndex reallocs: " <<
    outer_index_.getTotalReallocs() + outer_index_.getTotalReallocs() << endl;
}

void Graph::printAll() {
    cout << "*** OUTER ***\n";
    this->printAll(outer_index_, outer_buffer_);
    cout << "\n*** INNER ***\n";
    this->printAll(inner_index_, inner_buffer_);
}

void Graph::printAll(const Index &index, const Buffer &buffer)  {
    buffer.print();
    index.print();
    for (uint32_t node_id = 0 ; node_id < index.getCurSize() ; node_id++) {
        ListNodePos list_node_pos = index.getListHead(node_id).pos;
        if (list_node_pos.exists) {
            cout << "---Node " << node_id << " ListNodes --- " << endl;
            uint32_t pos = list_node_pos.pos;
            do {
                ListNode list_node = buffer.getListNode(pos);
                list_node.print();
                list_node_pos = list_node.getNextPos();
                if (! list_node_pos.exists) {
                    break;
                }
                pos = list_node_pos.pos;
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
    this->print(outer_index_, outer_buffer_);
    cout << "\n*** INNER ***\n";
    this->print(inner_index_, inner_buffer_);
}

void Graph::print(const Index &index, const Buffer &buffer) {
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
    for (unsigned int n = 0 ; n < size ; n++) {
        cout << array[n] << " ";
    }
    cout << endl;
}
