#include "Graph.hpp"

#include <cstring>
#include <time.h>

#include <iostream>

using namespace std;

Graph::~Graph() {
    // outer_index_.deleteNeigborsHash();
    // inner_index_.deleteNeigborsHash();
    // scc_outer_index_.deleteNeigborsHash();
    // scc_inner_index_.deleteNeigborsHash();
}

inline void Graph::insertNode(const uint32_t node_id) {
    outer_index_.insertNode(node_id);
    inner_index_.insertNode(node_id);
}

uint32_t Graph::insertNodes(const uint32_t &source_node_id, const uint32_t &target_node_id) {
    uint32_t min = source_node_id;
    uint32_t max = target_node_id;
    if (target_node_id < min) {
        min = target_node_id;
        max = source_node_id;
    }
    this->insertNode(max);
    this->insertNode(min);
    return min;
}

bool Graph::insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, const char &mode) {
    if (mode != 'S') {
        this->insertNodes(source_node_id, target_node_id);
    }
    const uint32_t *node1 = &source_node_id;
    const uint32_t *node2 = &target_node_id;
    NodeIndex *index;
    NodeIndex *mirror_index;
    Buffer *buffer;
    bool skip_search = false;
    if (mode != 'S') {
        index = &outer_index_;
        buffer = &outer_buffer_;
        mirror_index = &inner_index_;
    } else {
        index = &scc_outer_index_;
        buffer = &scc_outer_buffer_;
        mirror_index = &scc_inner_index_;
    }

    if (index->getListHeadNeighbors(*node1) > mirror_index->getListHeadNeighbors(*node2)) {
        this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer, mode);
    }
    if (this->insertEdge(*node1, *node2, index, buffer, mode, skip_search)) {
        skip_search = true;
        this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer, mode);
        this->insertEdge(*node1, *node2, index, buffer, mode, skip_search);
    } else {
        return false;
    }

    // if (index->getHashNeighbors(*node1, *node2) > mirror_index->getHashNeighbors(*node2, *node1)) {
    //     this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer, mode);
    // }
    // if (this->insertEdge(*node1, *node2, index, buffer, mode, skip_search)) {
    //     skip_search = true;
    //     this->toggleDirection(source_node_id, target_node_id, &node1, &node2, &index, &buffer, mode);
    //     this->insertEdge(*node1, *node2, index, buffer, mode, skip_search);
    // } else {
    //     return false;
    // }
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
        pos = first_pos;
    } else {
        pos = index->getListHead(source_node_id)->last_pos;
    }
    long last_pos;
    if (! buffer->insertNeighbor(pos, target_node_id, skip_search, &last_pos)) {
        return false;
    }
    // if (! skip_search) {
    //     if (! index->searchInsertHash(source_node_id, target_node_id, mode)) {
    //         return false;
    //     }
    // } else {
    //     index->insertNeighborInHash(source_node_id, target_node_id, mode);
    // }
    // pos = index->getListHead(source_node_id)->last_pos;
    // long feedback = buffer->insertNeighbor(pos, target_node_id, true);
    index->setListHeadNeighbors(source_node_id, index->getListHeadNeighbors(source_node_id) + 1);
    index->setListHeadLast(source_node_id, last_pos);
    return true;
}

inline void Graph::toggleDirection(const uint32_t &source_node_id, const uint32_t &target_node_id, const uint32_t **node1, const uint32_t **node2, NodeIndex **index, Buffer **buffer, const char &mode) {
    if (**node1 == source_node_id) {
        *node1 = &target_node_id;
        *node2 = &source_node_id;
        if (mode != 'S') {
            *index = &inner_index_;
            *buffer = &inner_buffer_;
        } else {
            *index = &scc_inner_index_;
            *buffer = &scc_inner_buffer_;
        }
    }
    else {
        *node1 = &source_node_id;
        *node2 = &target_node_id;
        if (mode != 'S') {
            *index = &outer_index_;
            *buffer = &outer_buffer_;
        } else {
            *index = &scc_outer_index_;
            *buffer = &scc_outer_buffer_;
        }
    }
}

uint32_t Graph::getNeighborsCount(const uint32_t &source, const char &direction) {
    NodeIndex *index;
    Buffer *buffer;
    if (direction == 'F') {
        index = &outer_index_;
    } else if (direction == 'B') {
        index = &inner_index_;
    } else if (direction == 'R') {
        index = &scc_outer_index_;
    } else if (direction == 'L') {
        index = &scc_inner_index_;
    }
    return index->getListHeadNeighbors(source);
}


void Graph::getNeighbors(const uint32_t &node_id, const char& direction, const char &randomness, Garray<uint32_t> &neighbors_array) {
    neighbors_array.clear();
    if (direction == 'F' || direction == 'B' || direction == 'L' || direction == 'R') {
        NodeIndex *index;
        Buffer *buffer;
        if (direction == 'F') {
            index = &outer_index_;
            buffer = &outer_buffer_;
        } else if (direction == 'B') {
            index = &inner_index_;
            buffer = &inner_buffer_;
        } else if (direction == 'R') {
            index = &scc_outer_index_;
            buffer = &scc_outer_buffer_;
        } else if (direction == 'L') {
            index = &scc_inner_index_;
            buffer = &scc_inner_buffer_;
        }
        uint32_t total_neighbors = index->getListHeadNeighbors(node_id);
        neighbors_array.increaseSize(total_neighbors);
        this->getNeighbors(node_id, *index, *buffer, neighbors_array);
    } else if (direction == 'A') {
        uint32_t total_neighbors = inner_index_.getListHeadNeighbors(node_id) + outer_index_.getListHeadNeighbors(node_id);
        neighbors_array.increaseSize(total_neighbors);
        getNeighbors(node_id, inner_index_, inner_buffer_, neighbors_array);
        getNeighbors(node_id, outer_index_, outer_buffer_, neighbors_array);
    }
    if (randomness) {
        uint32_t total_elements = neighbors_array.getElements();
        uint32_t swaps = total_elements * randomness / 200;
        swaps_ += swaps;
        while (swaps--) {
            uint32_t element1 = rand() % total_elements;
            uint32_t element2 = rand() % total_elements;
            uint32_t tmp = neighbors_array[element1];
            neighbors_array[element1] = neighbors_array[element2];
            neighbors_array[element2] = tmp;
        }
    }
}

void Graph::getNeighbors(const uint32_t &node_id, const NodeIndex &index, const Buffer &buffer, Garray<uint32_t> &neighbors_array) {
    long list_node_pos = index.getListHeadPos(node_id);
    if (list_node_pos != -1) {
        long pos = list_node_pos;
        do {
            ListNode *list_node = buffer.getListNode(pos);
            neighbors_array.pushBatch(list_node->getNeighborArray(), list_node->getNeighborNumber());
            list_node_pos = list_node->getNextPos();
            if (list_node_pos == -1) {
                break;
            }
            pos = list_node_pos;
        } while (1);
    }
}

uint32_t Graph::getNeighbor(const uint32_t &source, const uint32_t &neighbor, const char &direction, Garray<uint32_t> &neighbors_array) {
    NodeIndex *index;
    Buffer *buffer;
    if (direction == 'F') {
        index = &outer_index_;
        buffer = &outer_buffer_;
    } else if (direction == 'B') {
        index = &inner_index_;
        buffer = &inner_buffer_;
    } else if (direction == 'R') {
        index = &scc_outer_index_;
        buffer = &scc_outer_buffer_;
    } else if (direction == 'L') {
        index = &scc_inner_index_;
        buffer = &scc_inner_buffer_;
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
    cout << "\n*** SCC OUTER ***\n";
    this->printAll(scc_outer_index_, scc_outer_buffer_);
    cout << "\n*** SCC INNER ***\n";
    this->printAll(scc_inner_index_, scc_inner_buffer_);}

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
    cout << "\n*** SCC OUTER ***\n";
    this->print(scc_outer_index_, scc_outer_buffer_);
    cout << "\n*** SCC INNER ***\n";
    this->print(scc_inner_index_, scc_inner_buffer_);
}

void Graph::print(const NodeIndex &index, const Buffer &buffer) {
    for (uint32_t node = 0 ; node < index.getCurSize() ; node++) {
        Garray<uint32_t > neighbors;
        this->getNeighbors(node, index, buffer, neighbors);
         cout << "Node " << node << " has " << neighbors.getElements() << " neighbors:\n";
        neighbors.print();
        cout << "\n";
        //index.printNeighborsHash(node);
    }
    cout << endl;
}

void ExploredSet::init(const uint32_t &total_nodes) {
    explored_set_.init(total_nodes);
    explored_set_.setElements(total_nodes);
    for (uint32_t n = 0 ; n < total_nodes ; n++) {
        explored_set_[n] = 0;
    }
}

void ExploredSet::update(const uint32_t &total_nodes) {
    uint32_t old_elements = explored_set_.getElements();
    if (total_nodes <= old_elements) {
        return;
    }
    explored_set_.increaseSize(total_nodes);
    explored_set_.setElements(total_nodes);
    for (uint32_t n = old_elements ; n < total_nodes ; n++) {
        explored_set_[n] = 0;
    }
}

bool ExploredSet::checkMarkVisitedNode(const uint32_t &node_id, const unsigned long long &visit_version) {
    if (explored_set_[node_id] == visit_version) {
        return false;
    }
    explored_set_[node_id] = visit_version;
    return true;
}

bool ExploredSet::checkVisitedNode(const uint32_t &node_id, const unsigned long long &visit_version) {
    if (explored_set_[node_id] == visit_version) {
        return true;
    } else {
        return false;
    }
}
