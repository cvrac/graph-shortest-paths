#include "Graph.hpp"

#include <cstring>
#include <time.h>

#include <iostream>

#include "Array.hpp"

using namespace std;

Graph::~Graph() {
    outer_index_.deleteNeigborsHash();
    inner_index_.deleteNeigborsHash();
}

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
    NodeIndex *index = &outer_index_;
    Buffer *buffer = &outer_buffer_;
    bool skip_search = false;

    if (outer_index_.getHashNeighbors(*node1, *node2) > inner_index_.getHashNeighbors(*node2, *node1)) {
        this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer);
    }
    if (this->insertEdge(*node1, *node2, index, buffer, skip_search)) {
        skip_search = true;
        this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer);
        this->insertEdge(*node1, *node2, index, buffer, skip_search);
    }
    // clock_t end = clock();
    // cout << "edge insertion took " << static_cast<double>((end - start) / CLOCKS_PER_SEC) << endl;
}

bool Graph::insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, NodeIndex *index, Buffer *buffer, const bool &skip_search) {
    long first_pos = index->getListHead(source_node_id)->pos;
    if (first_pos == -1) {
        first_pos = buffer->allocNewNode();
        index->setListHeadPos(source_node_id, first_pos);
        index->setListHeadLast(source_node_id, first_pos);
    }
    long pos;
    if (! skip_search) {
        if (! index->searchInsertHash(source_node_id, target_node_id)) {
            return false;
        }
    }
    pos = index->getListHead(source_node_id)->last_pos;
    long feedback = buffer->insertNeighbor(pos, target_node_id, true);
    index->setListHeadNeighbors(source_node_id, index->getListHeadNeighbors(source_node_id) + 1);
    index->setListHeadLast(source_node_id, feedback);
    //index->insertNeighborInHash(source_node_id, target_node_id);
    return true;
}

void Graph::toggleDirection(const uint32_t &source_node_id, const uint32_t &target_node_id, const uint32_t **node1, const uint32_t **node2, NodeIndex **index, Buffer **buffer) {
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

uint32_t Graph::getNeighborsCount(const uint32_t &source, const char &direction) {
    NodeIndex *index;
    Buffer *buffer;
    if (direction == 'F') {
        index = &outer_index_;
    }
    else if (direction == 'B') {
        index = &inner_index_;
    }

    return index->getListHeadNeighbors(source);
}


NodeArray &Graph::getNeighbors(const uint32_t &node_id, const char& direction) {
    NodeIndex *index;
    Buffer *buffer;
    if (direction == 'F') {
        index = &outer_index_;
        buffer = &outer_buffer_;
    }
    else if (direction == 'B') {
        index = &inner_index_;
        buffer = &inner_buffer_;
    }

    return this->getNeighbors(node_id, *index, *buffer);
}

/* Caller should free after use */
NodeArray &Graph::getNeighbors(const uint32_t &node_id, const NodeIndex &index, const Buffer &buffer) {
    uint32_t total_neighbors = index.getListHeadNeighbors(node_id);

    if (node_array_.size < total_neighbors) {
        node_array_.size = (node_array_.size == 0) ? 1 : node_array_.size;
        while (node_array_.size <= total_neighbors) {
            node_array_.size *= 2;
        }
        uint32_t *old_array = node_array_.array;
        node_array_.array = new uint32_t[node_array_.size];
        delete[] old_array;
    }
    node_array_.count = total_neighbors;

    uint32_t cur_neighbor = 0;
    long list_node_pos = index.getListHeadPos(node_id);
    if (list_node_pos != -1) {
        long pos = list_node_pos;
        do {
            ListNode *list_node = buffer.getListNode(pos);
            uint32_t neighbors_to_add = list_node->getNeighborNumber();
            memcpy(&node_array_.array[cur_neighbor], list_node->getNeighborArray(), neighbors_to_add * sizeof(uint32_t));
            cur_neighbor += neighbors_to_add;

            list_node_pos = list_node->getNextPos();
            if (list_node_pos == -1) {
                break;
            }
            pos = list_node_pos;
        } while (1);
    }
    return node_array_;
}

uint32_t Graph::getStatistics() {
    cout << "Nodes: " << this->getNodes() << "\nAverage outer edges: " <<
    outer_index_.getAverageNeighbors() << "\nAverage inner edges: " <<
    inner_index_.getAverageNeighbors() << "\nBuffer reallocs: " <<
    outer_buffer_.getTotalReallocs() + inner_buffer_.getTotalReallocs() << "\nNodeIndex reallocs: " <<
    outer_index_.getTotalReallocs() + outer_index_.getTotalReallocs() << endl;
}

void Graph::printAll() {
    cout << "*** OUTER ***\n";
    this->printAll(outer_index_, outer_buffer_);
    cout << "\n*** INNER ***\n";
    this->printAll(inner_index_, inner_buffer_);
}

void Graph::printAll(const NodeIndex &index, const Buffer &buffer)  {
    buffer.print();
    index.print();
    for (uint32_t node_id = 0 ; node_id < index.getCurSize() ; node_id++) {
        long list_node_pos = index.getListHead(node_id)->pos;
        if (list_node_pos != -1) {
            cout << "---Node " << node_id << " ListNodes --- " << endl;
            long pos = list_node_pos;
            do {
                ListNode *list_node = buffer.getListNode(pos);
                list_node->print();
                list_node_pos = list_node->getNextPos();
                if (list_node_pos == -1) {
                    break;
                }
                pos = list_node_pos;
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

void Graph::print(const NodeIndex &index, const Buffer &buffer) {
    for (uint32_t node = 0 ; node < index.getCurSize() ; node++) {
        NodeArray &neighbors = this->getNeighbors(node, index, buffer);
        // cout << "Node " << node << " has " << (neighbors == NULL ? 0 : neighbors.count) << " neighbors:\n";
        neighbors.print();
        cout << "\n";
        index.printNeighborsHash(node);
    }
    cout << endl;
}

void NodeArray::print() {
    //cout << "--- NodeArray ---\n" << "size: " << size << endl;
    for (uint32_t n = 0 ; n < size ; n++) {
        cout << array[n] << " ";
    }
    cout << endl;
}
