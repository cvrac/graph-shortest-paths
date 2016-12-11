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
    GRAIL_ANSWER isReachableGrailIndex(uint32_t source_node, uint32_t target_node, const char &dir);

private:
    struct Vertex {
        Vertex() : childrenvisited(0), neighbors(NULL), total(0), visited(false) { }
        ~Vertex() {
            if (neighbors != NULL) {
                delete[] neighbors;
                neighbors = NULL;
            }
        }
        uint32_t childrenvisited;
        uint32_t *neighbors;
        uint32_t total;
        bool visited;
    };

    void createHyperGraph();
    void buildGrailIndex(const char &dir);
    void postOrderTraversal(const uint32_t &node, Vertex *vertices, Garray<uint32_t> & dfs_stack, uint32_t &order, uint32_t &index, const char &dir);
    bool subset(uint32_t &y1, uint32_t &y2, uint32_t &x1, uint32_t &x2) {
        return y1 >= x1 && y2 <= x2;
    }

    Garray<uint32_t> *outer_index_;
    Garray<uint32_t> *inner_index_;
    uint32_t run;
    Graph &graph_;
    SCC &str_components_;
};

#endif
