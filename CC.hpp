#ifndef GRAPHSHORTESTPATHS_CC_H
#define GRAPHSHORTESTPATHS_CC_H

#include "Graph.hpp"
#include "HashTable.hpp"
#include "Garray.hpp"

#define INITIAL_FRONTIER_ARRAY_SIZE 131

class CC {

public:
    CC(Graph &graph, const uint32_t &hash_size) : graph_(graph), explored_set_(hash_size),
                                                        frontier_outer_(INITIAL_FRONTIER_ARRAY_SIZE), frontier_inner_(INITIAL_FRONTIER_ARRAY_SIZE) {}
    ~CC();
    void estimateConnectedComponents();

private:
    void reset();

    Graph &graph_;
    HashTable<uint32_t > explored_set_;
    Garray<uint32_t > frontier_outer_;
    Garray<uint32_t > frontier_inner_;

};

#endif //GRAPHSHORTESTPATHS_CC_H
