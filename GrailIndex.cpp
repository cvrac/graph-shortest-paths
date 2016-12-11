#include "GrailIndex.hpp"

#include <iostream>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

GrailIndex::GrailIndex(Graph &gr, SCC &components) : run(2), graph_(gr), str_components_(components)
{ }

GrailIndex::~GrailIndex() { }

/*Creation of the hypergraph and the grail index*/
void GrailIndex::buildGrailIndex() {
    createHyperGraph();
    buildGrailIndex('R');
    buildGrailIndex('L');
}

void GrailIndex::buildGrailIndex(const char &dir) {
    uint32_t end = graph_.getNodes('S');
    Garray<Garray<uint32_t> > &scc_index = (dir == 'R' ? outer_index_ : inner_index_);
    Garray<uint32_t> dfs_stack;
    Garray<Vertex> vertices(end);
    scc_index.init(end);
    // cout << str_components_.getSccNumber() << endl;
    // scc_index.init(graph_.getNodes('S'));
    // cout << scc_index.getSize() << endl;

    // scc_index = new Garray<uint32_t>[graph_.getNodes('S')];
    // assert(scc_index != NULL);

    srand((unsigned) time(NULL));

    for (uint32_t i = 0; i < end; i++) {
        Garray<uint32_t> &neighbors = graph_.getNeighbors(i, dir);
        vertices[i].total = neighbors.getElements();
        vertices[i].neighbors = new uint32_t[vertices[i].total];
        memcpy(vertices[i].neighbors, neighbors.retVal(), vertices[i].total * sizeof(uint32_t));
    }


    uint32_t root, order;
    for (uint32_t index = 0; index < run * 2; index += 2) {
        order = 1;
        if (!index)
            root = 0;
        else
            root = rand() % end;
        postOrderTraversal(root, vertices, dfs_stack, order, index, dir);
        for (uint32_t i = 0; i < end; i++) {
            if (vertices[i].visited == false)
                postOrderTraversal(i, vertices, dfs_stack, order, index, dir);
        }
        for (uint32_t i = 0; i < end; i++) {
            vertices[i].childrenvisited = 0;
            vertices[i].visited = false;
        }
    }

     //graph_.print();
     //for (uint32_t i = 0; i < graph_.getNodes('S'); i++)
     //   scc_index[i].print();
}

/*Given the set of strongly connected components, creates the hypergraph
 *of the initial graph, which is stored in the same Graph structure, as
 *the initial
 */
void GrailIndex::createHyperGraph() {
    graph_.initSccHypergraph(str_components_.getSccNumber());
    str_components_.addSccNeighbors();
}


void GrailIndex::postOrderTraversal(const uint32_t &node, Garray<Vertex> &vertices, Garray<uint32_t> &dfs_stack, uint32_t &order, uint32_t &index, const char &dir) {
    uint32_t v, w;
    Garray<Garray<uint32_t> > &scc_index = (dir == 'R' ? outer_index_ : inner_index_);
    dfs_stack.enstack(node);

    while (dfs_stack.isEmpty() == false) {
        v = dfs_stack.top();
        if (vertices[v].visited == false) {
            vertices[v].visited = true;
            if (vertices[v].total == 0) {
                v = dfs_stack.popBack();
                // if (v >= graph_.getNodes('S'))
                //     cout << "v sucks" << v << endl;
                Garray<uint32_t> &val_array = scc_index[v];
                // cout << "foo" << endl;
                val_array.enstack(order);
                val_array.enstack(order);
                ++order;
                continue;
            }
        }
        if (vertices[v].childrenvisited < vertices[v].total) {
            w = vertices[v].neighbors[vertices[v].childrenvisited];
            // cout << v << " " << w << endl;
            if (vertices[w].visited == false)
                dfs_stack.enstack(w);
            ++vertices[v].childrenvisited;
        } else {
            v = dfs_stack.popBack();
            long minrank = -1;

            for (uint32_t i = 0; i < vertices[v].total; i++) {
                w = vertices[v].neighbors[i];
                Garray<uint32_t> &val_array = scc_index[w];
                if (minrank == -1)
                    minrank = val_array[index];
                else {
                    minrank = (val_array[index] < minrank) ? val_array[index] : minrank;
                }
            }

            Garray<uint32_t> &val_array = scc_index[v];
            val_array.enstack(minrank);
            val_array.enstack(order);
            ++order;
        }
    }

    dfs_stack.clear();
}

GRAIL_ANSWER GrailIndex::isReachableGrailIndex(uint32_t source_node, uint32_t target_node, const char &dir) {
    Garray<Garray<uint32_t> > &scc_index = (dir == 'R' ? outer_index_ : inner_index_);
    uint32_t id1 = str_components_.findNodeStronglyConnectedComponentID(source_node);
    uint32_t id2 = str_components_.findNodeStronglyConnectedComponentID(target_node);

    if (!subset(scc_index[id2][0], scc_index[id2][1], scc_index[id1][0], scc_index[id1][1]))
        return NO;
    else return MAYBE;
    /*if (!subset(scc_index[id2][2], scc_index[id2][3], scc_index[id1][2], scc_index[id1][3]))
        return NO;
    if (!subset(scc_index[id2][4], scc_index[id2][5], scc_index[id1][4], scc_index[id1][5]))
        return NO;*/
}
