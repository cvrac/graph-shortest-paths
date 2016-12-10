#include "Graph.hpp"

#include <cstring>
#include <time.h>

#include <iostream>

using namespace std;

Graph::~Graph() {
    outer_index_.deleteNeigborsHash();
    inner_index_.deleteNeigborsHash();
    scc_index_.deleteNeigborsHash();
}

inline void Graph::insertNode(const uint32_t node_id, const char &mode) {
    if (mode == 'N') {
        outer_index_.insertNode(node_id);
        inner_index_.insertNode(node_id);
    } else if (mode == 'S') {
        scc_index_.insertNode(node_id);
    }
}

uint32_t Graph::insertNodes(const uint32_t &source_node_id, const uint32_t &target_node_id, const char &mode) {
    uint32_t min = source_node_id;
    uint32_t max = target_node_id;
    if (target_node_id < min) {
        min = target_node_id;
        max = source_node_id;
    }
    this->insertNode(max, mode);
    this->insertNode(min, mode);
    /*if (bidirectional) {
        //bidirectional_index_.insertNode(min);
        bidirectional_index_.insertNode(max);
    }*/
    return min;
}

bool Graph::insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, const char &mode) {
    if (mode == 'S') {
        return this->insertEdge(source_node_id, target_node_id, &scc_index_, &scc_buffer_, mode, false);
    }
    const uint32_t min = this->insertNodes(source_node_id, target_node_id, mode);
    // clock_t start = clock();
    const uint32_t *node1 = &source_node_id;
    const uint32_t *node2 = &target_node_id;
    NodeIndex *index = &outer_index_;
    Buffer *buffer = &outer_buffer_;
    bool skip_search = false;

    if (outer_index_.getHashNeighbors(*node1, *node2) > inner_index_.getHashNeighbors(*node2, *node1)) {
        this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer);
    }
    if (this->insertEdge(*node1, *node2, index, buffer, mode, skip_search)) {
        skip_search = true;
        this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer);
        this->insertEdge(*node1, *node2, index, buffer, mode, skip_search);
    } else {
        return false;
    }
    /*if (bidirectional) {
        this->insertEdge(source_node_id, target_node_id, &this->bidirectional_index_, &this->bidirectional_buffer_, true);
        this->insertEdge(target_node_id, source_node_id, &this->bidirectional_index_, &this->bidirectional_buffer_, true);
    }*/
    // clock_t end = clock();
    // cout << "edge insertion took " << static_cast<double>((end - start) / CLOCKS_PER_SEC) << endl;
    return true;
}

bool Graph::insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, NodeIndex *index, Buffer *buffer, const char &mode, const bool &skip_search) {
    long first_pos = index->getListHead(source_node_id)->pos;
    if (first_pos == -1) {
        first_pos = buffer->allocNewNode();
        index->setListHeadPos(source_node_id, first_pos);
        index->setListHeadLast(source_node_id, first_pos);
    }
    long pos;
    if (! skip_search) {
        if (! index->searchInsertHash(source_node_id, target_node_id, mode)) {
            return false;
        }
    }
    pos = index->getListHead(source_node_id)->last_pos;
    long feedback = buffer->insertNeighbor(pos, target_node_id, true);
    index->setListHeadNeighbors(source_node_id, index->getListHeadNeighbors(source_node_id) + 1);
    index->setListHeadLast(source_node_id, feedback);
    return true;
}

inline void Graph::toggleDirection(const uint32_t &source_node_id, const uint32_t &target_node_id, const uint32_t **node1, const uint32_t **node2, NodeIndex **index, Buffer **buffer) {
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
    } else if (direction == 'B') {
        index = &inner_index_;
    } else if (direction == 'S') {
        index = &scc_index_;
    }
    return index->getListHeadNeighbors(source);
}


Garray<uint32_t> &Graph::getNeighbors(const uint32_t &node_id, const char& direction) {
    neighbors_array_.clear();
    if (direction == 'F' || direction == 'B' || direction == 'S') {
        NodeIndex *index;
        Buffer *buffer;
        if (direction == 'F') {
            index = &outer_index_;
            buffer = &outer_buffer_;
        } else if (direction == 'B') {
            index = &inner_index_;
            buffer = &inner_buffer_;
        } else if (direction == 'S') {
            index = &scc_index_;
            buffer = &scc_buffer_;
        }
        uint32_t total_neighbors = index->getListHeadNeighbors(node_id);
        neighbors_array_.increaseSize(total_neighbors);
        return this->getNeighbors(node_id, *index, *buffer);
    } else if (direction == 'A') {
        uint32_t total_neighbors = inner_index_.getListHeadNeighbors(node_id) + outer_index_.getListHeadNeighbors(node_id);
        neighbors_array_.increaseSize(total_neighbors);
        getNeighbors(node_id, inner_index_, inner_buffer_);
        return getNeighbors(node_id, outer_index_, outer_buffer_);
    }
}

Garray<uint32_t> &Graph::getNeighbors(const uint32_t &node_id, const NodeIndex &index, const Buffer &buffer) {
    long list_node_pos = index.getListHeadPos(node_id);
    if (list_node_pos != -1) {
        long pos = list_node_pos;
        do {
            ListNode *list_node = buffer.getListNode(pos);
            neighbors_array_.pushBatch(list_node->getNeighborArray(), list_node->getNeighborNumber());
            list_node_pos = list_node->getNextPos();
            if (list_node_pos == -1) {
                break;
            }
            pos = list_node_pos;
        } while (1);
    }
    return neighbors_array_;
}

uint32_t Graph::getNeighbor(const uint32_t &source, const uint32_t &neighbor, const char &direction) {
    NodeIndex *index;
    Buffer *buffer;
    if (direction == 'F') {
        index = &outer_index_;
        buffer = &outer_buffer_;
    } else if (direction == 'B') {
        index = &inner_index_;
        buffer = &inner_buffer_;
    } else if (direction == 'S') {
        index = &scc_index_;
        buffer = &scc_buffer_;
    }

    long list_node_pos = index->getListHeadPos(source);
    uint32_t i = neighbor;
    if (list_node_pos != -1) {
        long pos = list_node_pos;
        do {
            ListNode *list_node = buffer->getListNode(pos);
            uint32_t list_node_max_size = list_node->getNeighborNumber();
            uint32_t *neighbors_arr = list_node->getNeighborArray();
            if (i < list_node_max_size)
                return neighbors_arr[i];
            list_node_pos = list_node->getNextPos();
            if (list_node_pos == -1)
                break;
            pos = list_node_pos;
            i -= list_node_max_size;
        } while (1);
    }
    // cout << neighbor << endl;
}


bool Graph::checkMarkVisitedNode(const uint32_t &node_id, const char &direction, const unsigned long long &visit_version) {
    NodeIndex *index;
    if (direction == 'F') {
        index = &outer_index_;
    } else if (direction == 'B') {
        index = &inner_index_;
    } else if (direction == 'S') {
        index = &scc_index_;
    }
    return index->checkSetListHeadVisitedVersion(node_id, visit_version);
}

bool Graph::checkVisitedNode(const uint32_t &node_id, const char &direction, const unsigned long long &visit_version) {
    NodeIndex *index;
    if (direction == 'F') {
        index = &outer_index_;
    } else if (direction == 'B') {
        index = &inner_index_;
    } else if (direction == 'S') {
        index = &scc_index_;
    }
    return index->checkListHeadVisitedVersion(node_id, visit_version);
}

uint32_t Graph::getStatistics() {
    cout << "Nodes: " << this->getNodes('N') << "\nAverage outer edges: " <<
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
    cout << "\n*** SCC ***\n";
    this->printAll(scc_index_, scc_buffer_);}

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

void Graph::print() {
    cout << "*** OUTER ***\n";
    this->print(outer_index_, outer_buffer_);
    cout << "\n*** INNER ***\n";
    this->print(inner_index_, inner_buffer_);
    cout << "\n*** INNER ***\n";
    this->print(inner_index_, inner_buffer_);
    cout << "\n*** SCC ***\n";
    this->print(scc_index_, scc_buffer_);

}

void Graph::print(const NodeIndex &index, const Buffer &buffer) {
    for (uint32_t node = 0 ; node < index.getCurSize() ; node++) {
        neighbors_array_.clear();
        Garray<uint32_t > &neighbors = this->getNeighbors(node, index, buffer);
         cout << "Node " << node << " has " << neighbors.getElements() << " neighbors:\n";
        neighbors.print();
        cout << "\n";
        //index.printNeighborsHash(node);
    }
    cout << endl;
}
