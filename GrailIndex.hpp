#ifndef GRAPHSHORTESTPATHS_GRAILINDEX_H
#define GRAPHSHORTESTPATHS_GRAILINDEX_H

#include "SCC.hpp"
#include "Graph.hpp"
#include "Garray.hpp"

enum GRAIL_ANSWER {NO = 0, MAYBE = 1, YES = 2};

class GrailIndex {
public:
    GrailIndex(Graph &gr, SCC &components);
    ~GrailIndex();
    void buildGrailIndex();
    GRAIL_ANSWER isReachableGrailIndex(uint32_t source_node, uint32_t target_node);

private:
    struct Vertex {
        Vertex() : node_id_(0), parent_id_(0), index_(0), lowlink_(0), childrenvisited(0), neighbors(NULL), total(0), visited(false) { }
        ~Vertex() {
            if (neighbors != NULL) {
                delete[] neighbors;
                neighbors = NULL;
            }
        }
        uint32_t node_id_;
        uint32_t parent_id_;
        uint32_t index_;
        uint32_t lowlink_;
        uint32_t childrenvisited;
        uint32_t *neighbors;
        uint32_t total;
        bool visited;
    };

    void createHyperGraph();
    void postOrderTraversal(const uint32_t &node, Vertex *vertices, Garray<uint32_t> & dfs_stack);
    bool subset(Garray<uint32_t> &y, Garray<uint32_t> &x) {
        return y[0] >= x[0] && y[1] <= x[1];
    }

    Garray<Garray<uint32_t> > index_;
    Graph &graph_;
    SCC &str_components_;
};

#endif
