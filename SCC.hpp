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
    void init();
    void print();

private:
    struct Component {
        Component(uint32_t &id);
        Component();
        ~Component();
        void increaseSize(uint32_t &size) { this->included_node_ids.increaseSize(size); }

        uint32_t component_id;
        uint32_t included_nodes_count;
        Garray<uint32_t> included_node_ids;
        // Component& operator= (const Component &comp);
    };

    class ComponentCursor {
        Component *component_ptr;
    };

    struct Vertex {
        Vertex() : node_id_(0), parent_id_(0), index_(0), lowlink_(0), last_neighbor_(0), onStack(false), neighbors(NULL), total(0) { }
        uint32_t node_id_;
        uint32_t parent_id_;
        uint32_t index_;
        uint32_t lowlink_;
        long last_neighbor_;
        uint32_t *neighbors;
        uint32_t total;
        bool onStack;
    };

    void tarjanAlgorithm();
    void stronglyConnected(uint32_t &node, Garray<uint32_t> &tarj_stack, HashTable<uint32_t> &visited, Vertex *vertices, uint32_t *index);

    Graph &graph;
    Garray<Component> components_;
    uint32_t components_count_;
    uint32_t inverted_index_size_;
    uint32_t *id_belongs_to_component_;
};

#endif
