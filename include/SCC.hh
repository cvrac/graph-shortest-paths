#ifndef GRAPHSHORTESTPATHS_SCC_H
#define GRAPHSHORTESTPATHS_SCC_H

#include <stdint.h>

#include "Graph.hh"
#include "Garray.hh"
#include "ShortestPath.hh"

class ShortestPath;
class Graph;

class SCC {

    class ComponentCursor;

public:

    SCC(Graph &prgraph);
    ~SCC();
    void estimateStronglyConnectedComponents();
    int findNodeStronglyConnectedComponentID(uint32_t &node_id) {return id_belongs_to_component_[node_id];}
    void iterateStronglyConnectedComponentID(ComponentCursor *cursor);
    bool nextStronglyConnectedComponentID(ComponentCursor *cursor);
    // int estimateShortestPathStronglyConnectedComponents(uint32_t &source, uint32_t &target);
    uint32_t getSccNumber() { return this->components_.getElements(); }
    void addSccNeighbors();
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

    struct Vertex {
        Vertex() : parent_id_(0), index_(0), lowlink_(0), childrenvisited(0), neighbors(NULL), total(0), onStack(false), visited(false) { }
        ~Vertex() {
            if (neighbors != NULL) {
                delete[] neighbors;
                neighbors = NULL;
            }
        }
        uint32_t parent_id_;
        uint32_t index_;
        uint32_t lowlink_;
        uint32_t childrenvisited;
        uint32_t *neighbors;
        uint32_t total;
        bool onStack;
        bool visited;
    };

    struct ComponentCursor {

        ComponentCursor() : component_ptr_(NULL), next(0) {}

        Component *component_ptr_;
        uint32_t next;
    };

    void tarjanAlgorithm();
    void stronglyConnected(uint32_t &node, Garray<uint32_t> &dfs_stack, Garray<uint32_t> &tarj_stack, Garray<Vertex> &vertices, uint32_t *index);

    Graph &graph;
    Garray<Component> components_;
    Garray<uint32_t> id_belongs_to_component_;
    Garray<uint32_t> neighbors_;
};


#endif
