#ifndef GRAPHSHORTESTPATHS_SCC_H
#define GRAPHSHORTESTPATHS_SCC_H

#include <stdint.h>

#include "Graph.hpp"
#include "Garray.hpp"

class Graph;

class SCC {

public:
    SCC(const uint32_t &size, Graph &prgraph);
    ~SCC();
    void estimateStronglyConnectedComponents();
    int findNodeStronglyConnectedComponentID(uint32_t &node_id);
    void iterateStronglyConnectedComponentID();
    bool nextStronglyConnectedComponentID();
    int estimateShortestPathStronglyConnectedComponents(Graph &graph, uint32_t &source, uint32_t &target);

private:
    struct Component {
        Component();
        ~Component();

        uint32_t component_id;
        uint32_t included_nodes_count;
        Garray<uint32_t> included_node_ids;
    };

    class ComponentCursor {
        Component *component_ptr;
    };

    struct Vertex {
        uint32_t node_id_;
        uint32_t index_;
        uint32_t lowlink_;
    };

    void tarjanAlgorithm();
    void stronglyConnected(uint32_t &node);

    Graph &graph;
    Garray<Component> components_;
    uint32_t components_count_;
    uint32_t inverted_index_size_;
    Garray<uint32_t> id_belongs_to_component_;
};

#endif
