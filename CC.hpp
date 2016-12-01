#ifndef GRAPHSHORTESTPATHS_CC_H
#define GRAPHSHORTESTPATHS_CC_H

#include "Graph.hpp"
#include "HashTable.hpp"
#include "Garray.hpp"

#define INITIAL_FRONTIER_ARRAY_SIZE 131
#define HASH_SIZE 3

class CC {

public:
    struct UpdateCell {
        UpdateCell() : neighbor_(0), neighbor_exists_(false), ptr_(0), ptr_exists_(false) {}
        void print();

        uint32_t neighbor_;
        uint32_t ptr_;
        bool neighbor_exists_;
        bool ptr_exists_;
    };

    CC(Graph &graph, const float &threshold) : graph_(graph), frontier_(INITIAL_FRONTIER_ARRAY_SIZE), visit_version_(0),
                                               queries_count_(0), update_index_use_count_(0), threshold_(threshold), total_rebuilds_(0) {}
    ~CC();
    void estimateConnectedComponents();
    void insertNewEdge(const uint32_t &source_node, const uint32_t &target_node);
    bool sameConnectedComponent(const uint32_t &source_node, const uint32_t &target_node);
    void rebuildIndexes() {total_rebuilds_++; this->estimateConnectedComponents();}
    bool needRebuilding() const {//cout << (float) (update_index_use_count_) / queries_count_ << endl;
                                return (float) (update_index_use_count_) / queries_count_ > threshold_;}
    uint32_t getTotalRebuilds() const {return total_rebuilds_;}
    void print();

private:
    void reset();

    Graph &graph_;
    Garray<uint32_t> frontier_;
    Garray<uint32_t> ccindex_;
    Garray<UpdateCell> update_index_;
    unsigned long long visit_version_;
    uint32_t queries_count_;
    uint32_t update_index_use_count_;
    float threshold_;
    uint32_t total_rebuilds_;
};

#endif //GRAPHSHORTESTPATHS_CC_H
