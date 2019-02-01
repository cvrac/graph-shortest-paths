#ifndef GRAPHSHORTESTPATHS_CC_H
#define GRAPHSHORTESTPATHS_CC_H

#include "Graph.hh"
#include "HashTable.hh"
#include "Garray.hh"

#define INITIAL_FRONTIER_ARRAY_SIZE 131
#define THRESHOLD 1

class CC {

public:
    struct UpdateCell {
        UpdateCell() : neighbor(0), index_version(0), graph_version(0) {}

        uint32_t neighbor;
        long graph_version; /* For multi threading with dynamic edge additions */
        long index_version; /* Used to mark visited cells; at each visit, set to CC::index_version_ */
    };

    CC(Graph &graph) : graph_(graph), frontier_(INITIAL_FRONTIER_ARRAY_SIZE), index_version_(0),
                                               queries_count_(0), update_index_use_count_(0), threshold_(THRESHOLD), total_rebuilds_(0),
                                               explored_set_(graph), neighbors_(INITIAL_NEIGHBORS_ARRAY_SIZE) {}
    ~CC();
    void estimateConnectedComponents();
    void insertNewEdge(const uint32_t &source_node, const uint32_t &target_node, const long &graph_version);
    bool sameConnectedComponent(const uint32_t &source_node, const uint32_t &target_node, const long &graph_version);
    void rebuildIndexes() {total_rebuilds_++; this->estimateConnectedComponents();}
    bool needRebuilding() const {//cout << (float) (update_index_use_count_) / queries_count_ << " -> " << update_index_use_count_ << "\n\n";
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
    void init();

    Graph &graph_;
    Garray<uint32_t> frontier_;
    Garray<uint32_t> ccindex_;
    Garray<UpdateCell> update_index_;
    ExploredSet explored_set_;
    Garray<uint32_t> neighbors_;
    unsigned long long index_version_;
    uint32_t queries_count_;
    uint32_t update_index_use_count_;
    float threshold_;
    uint32_t total_rebuilds_;
};

#endif //GRAPHSHORTESTPATHS_CC_H
