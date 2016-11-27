#ifndef GRAPHSHORTESTPATHS_CC_H
#define GRAPHSHORTESTPATHS_CC_H

#include "Graph.hpp"
#include "HashTable.hpp"
#include "Garray.hpp"

#define INITIAL_FRONTIER_ARRAY_SIZE 131
#define HASH_SIZE 3

class CC {

public:
    CC(Graph &graph, const uint32_t &hash_size) : graph_(graph), frontier_(INITIAL_FRONTIER_ARRAY_SIZE), visited_flag_(false) {}
    ~CC();
    void estimateConnectedComponents();
    void insertNewEdge(const uint32_t &source_node, const uint32_t &target_node);
    void print();

private:
    struct UpdateCell {
        UpdateCell() : merged_with(NULL) {}
        ~UpdateCell() {if (merged_with != NULL) delete merged_with;}

        HashTable<uint32_t > *merged_with; // Allocate only when needed
    };

    void reset();

    Graph &graph_;
    Garray<uint32_t> frontier_;
    Garray<uint32_t> ccindex_;
    Garray<UpdateCell> update_index_;
    bool visited_flag_;

};

#endif //GRAPHSHORTESTPATHS_CC_H
