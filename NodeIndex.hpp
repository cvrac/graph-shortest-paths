#ifndef GRAPHSHORTESTPATHS_INDEX_H
#define GRAPHSHORTESTPATHS_INDEX_H

#include <stdint.h>

#include "HashTable.hpp"

// Test size: 3

#define HASH_SIZE 3
#define HASH_SIZE_SCC 1 

class SCC;

class NodeIndex {

    struct ListHead;

public:
    friend class SCC;

    NodeIndex(const uint32_t &size);
    ~NodeIndex();
    void init(const uint32_t &size);
    void insertNode(const uint32_t &node_id);
    ListHead *getListHead(const uint32_t &node_id) const {return &index_[node_id];}
    uint32_t getCurSize() const {return cur_size_;}
    void setListHeadPos(const uint32_t &node_id, const long &head) {index_[node_id].pos = head;}
    void setListHeadLast(const uint32_t &node_id, const long &last) {index_[node_id].last_pos = last;}
    void setListHeadNeighbors(const uint32_t &node_id, const uint32_t &n) {index_[node_id].total_neighbors = n;}
    void insertNeighborInHash(const uint32_t &node_id, const uint32_t &neighbor_id, const char &mode);
    bool searchNeighborInHash(const uint32_t &node_id, const uint32_t &neighbor_id);
    bool searchInsertHash(const uint32_t &node_id, const uint32_t &neighbor_id, const char &mode);
    uint32_t getListHeadNeighbors(const uint32_t &node_id) const {return index_[node_id].total_neighbors;}
    bool checkSetListHeadVisitedVersion(const uint32_t &node_id, const unsigned long long &visit_version);
    bool checkListHeadVisitedVersion(const uint32_t &node_id, const unsigned long long &visit_version)
        {if (index_[node_id].visit_version_ == visit_version) return true; else return false;}
    bool checkSetListHeadCCFlag(const uint32_t &node_id, const bool &cc_flag);
    uint32_t getHashNeighbors(const uint32_t &source, const uint32_t &target) const {
        if (index_[source].neighbors_hash_ == NULL) {
            return 0;
        }
        return index_[source].neighbors_hash_->getBucketCount(target);
    }
    long getListHeadPos(const uint32_t &node_id) const {return index_[node_id].pos;}
    uint32_t getAverageNeighbors();
    uint32_t getTotalReallocs() const {return total_reallocs_;}
    uint32_t getMaxSize() const {return max_size_;}
    void print() const;
    void printNeighborsHash(const uint32_t &node_id) const;
    void deleteNeigborsHash();

private:
    struct ListHead {
        friend class SCC;

        ListHead() : pos(-1), last_pos(-1), total_neighbors(0), neighbors_hash_(NULL), visit_version_(0), cc_flag_(false) {
            //neighbors_hash_ = new HashTable(HASH_SIZE);
        }

        long pos;
        long last_pos;
        uint32_t total_neighbors;
        HashTable<uint32_t> *neighbors_hash_; // Allocate only when needed
        unsigned long long visit_version_;
        bool cc_flag_; // Similar to visit_version_, suitable for search that always visits the whole graph
    };

    ListHead *index_;
    uint32_t cur_size_;
    uint32_t max_size_;
    uint32_t total_reallocs_;

};


#endif //GRAPHSHORTESTPATHS_INDEX_H
