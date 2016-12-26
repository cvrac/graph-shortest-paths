#ifndef GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
#define GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H

#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "SCC.hpp"
#include "CC.hpp"
#include "GrailIndex.hpp"
#include "JobScheduler.hpp"

class OperationsControl {

public:
    OperationsControl(const float &cc_threshold, const uint8_t pool_size);
    ~OperationsControl();
    void run(const char &mode);
    // int estimateShortestPathStronglyConnected(uint32_t &source, uint32_t &target);
    // int estimateShortestPath(uint32_t &source, uint32_t &target);

private:
    void buildGraph(const char &mode);
    void runQueries(const char &mode);
    void parseNodeIds(uint32_t *source, uint32_t *target);

    Graph graph_;
    Garray<ShortestPath *> paths_;
    SCC strongly_conn_;
    CC connected_components_;
    GrailIndex grail_index_;
    Garray<int> res_array_;
    JobScheduler scheduler_;
};

#endif //GRAPHSHORTESTPATHS_OPERATIONSCONTROL_H
