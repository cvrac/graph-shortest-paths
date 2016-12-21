#ifndef GRAPHSHORTESTPATHS_CC_H
#define GRAPHSHORTESTPATHS_CC_H

#include "Graph.hpp"
#include "HashTable.hpp"
#include "Garray.hpp"

#define INITIAL_FRONTIER_ARRAY_SIZE 131

class CC {

public:
    struct UpdateCell {
        UpdateCell() : neighbor_(0), visit_version_(0) {}

        uint32_t neighbor_;
        unsigned long long visit_version_;
    };

    CC(Graph &graph, const float &threshold) : graph_(graph), frontier_(INITIAL_FRONTIER_ARRAY_SIZE), cc_flag_(false), visit_version_(0),
                                               queries_count_(0), update_index_use_count_(0), threshold_(threshold), total_rebuilds_(0) {}
    ~CC();
    void estimateConnectedComponents();
    void insertNewEdge(const uint32_t &source_node, const uint32_t &target_node);
    bool sameConnectedComponent(const uint32_t &source_node, const uint32_t &target_node);
    void rebuildIndexes() {total_rebuilds_++; this->estimateConnectedComponents();}
    bool needRebuilding() const {//cout << (float) (update_index_use_count_) / queries_count_ << " -> " << update_index_use_count_ << endl;
                            return (float) (update_index_use_count_) / queries_count_ > threshold_;}
    uint32_t getTotalRebuilds() const {return total_rebuilds_;}
    float getThreshold() const {return threshold_;}
    uint32_t getUpdateIndexUseCount() const {return update_index_use_count_;}
    void setQueriesCount(const uint32_t &queries_count) {queries_count_ = queries_count;}
    void setUpdateIndexUseCount(const uint32_t &update_index_use_count) {update_index_use_count_ = update_index_use_count;}
    uint32_t findNodeConnectedComponentID(const uint32_t &node) {return ccindex_[node];}
    void print();

private:
    void reset();

    Graph &graph_;
    Garray<uint32_t> frontier_;
    Garray<uint32_t> ccindex_;
    Garray<UpdateCell> update_index_;
    unsigned long long visit_version_;
    bool cc_flag_;
    uint32_t queries_count_;
    uint32_t update_index_use_count_;
    float threshold_;
    uint32_t total_rebuilds_;
};

#endif //GRAPHSHORTESTPATHS_CC_H
