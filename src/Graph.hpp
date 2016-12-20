#ifndef GRAPHSHORTESTPATHS_GRAPH_H
#define GRAPHSHORTESTPATHS_GRAPH_H

#include "NodeIndex.hpp"
#include "Buffer.hpp"
#include "HashTable.hpp"
#include "Garray.hpp"

#define INITIAL_INDEX_MAX_SIZE 100000
#define INITIAL_MAX_LIST_NODES 20000
#define INITIAL_MAX_LIST_NODES_SCC 10000
#define INITIAL_NEIGHBORS_ARRAY_SIZE 131

class Graph {

public:
    friend class CC;
    friend class SCC;
    Graph() : neighbors_array_(INITIAL_NEIGHBORS_ARRAY_SIZE),
              outer_index_(INITIAL_INDEX_MAX_SIZE), inner_index_(INITIAL_INDEX_MAX_SIZE),
              outer_buffer_(INITIAL_MAX_LIST_NODES), inner_buffer_(INITIAL_MAX_LIST_NODES),
              scc_outer_index_(0), scc_outer_buffer_(0),
              scc_inner_index_(0), scc_inner_buffer_(0), swaps_(0) {}
    ~Graph();
    bool insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, const char &mode);
    Garray<uint32_t> &getNeighbors(const uint32_t &node_id, const char &direction, const char &randomness);
    uint32_t getNeighborsCount(const uint32_t &source, const char &direction);
    uint32_t getNeighbor(const uint32_t &source, const uint32_t &neighbor, const char &direction);
    uint32_t getNodes(const char &mode) {
        if (mode == 'S') {
            return scc_outer_index_.getCurSize();
        }
        return outer_index_.getCurSize();}
    uint32_t getStatistics();
    bool checkMarkVisitedNode(const uint32_t &node_id, const char &direction, const unsigned long long &visit_version);
    bool checkVisitedNode(const uint32_t &node_id, const char &direction, const unsigned long long &visit_version);
    bool checkMarkCCFlag(const uint32_t &node_id, const bool &cc_flag, const char &mode) {
        if (mode == 'R') {
            return scc_outer_index_.checkSetListHeadCCFlag(node_id, cc_flag);
        } else if (mode == 'L') {
            return scc_inner_index_.checkSetListHeadCCFlag(node_id, cc_flag);
        }
        return outer_index_.checkSetListHeadCCFlag(node_id, cc_flag);}
    void initSccHypergraph(const uint32_t &size) {scc_outer_index_.init(size); scc_inner_index_.init(size);
    scc_outer_buffer_.init(INITIAL_MAX_LIST_NODES_SCC); scc_inner_buffer_.init(INITIAL_MAX_LIST_NODES_SCC); }
    void printAll();
    void print();
    uint32_t swaps_;

private:
    bool insertEdge(const uint32_t &source_node_id, const uint32_t &target_node_id, NodeIndex *index, Buffer *buffer, const char &mode, const bool &skip_search);
    uint32_t insertNodes(const uint32_t &source_node_id, const uint32_t &target_node_id);
    void insertNode(const uint32_t node_id);
    void toggleDirection(const uint32_t &source_node_id, const uint32_t &target_node_id, const uint32_t **node1, const uint32_t **node2, NodeIndex **index, Buffer **buffer, const char &mode);
    Garray<uint32_t> &getNeighbors(const uint32_t &node_id, const NodeIndex &index, const Buffer &buffer);
    void printAll(const NodeIndex &index, const Buffer &buffer);
    void print(const NodeIndex &index, const Buffer &buffer);

    Garray<uint32_t > neighbors_array_;
    NodeIndex outer_index_;
    Buffer outer_buffer_;
    NodeIndex inner_index_;
    Buffer inner_buffer_;

    NodeIndex scc_outer_index_;
    Buffer scc_outer_buffer_;
    NodeIndex scc_inner_index_;
    Buffer scc_inner_buffer_;

};


#endif //GRAPHSHORTESTPATHS_GRAPH_H
