#include "GrailIndex.hpp"

#include <iostream>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

GrailIndex::GrailIndex(Graph &gr, SCC &components) : index_(NULL), graph_(gr), str_components_(components)
{ }

GrailIndex::~GrailIndex() {
    if (index_ != NULL) {
        delete[] index_;
        index_ = NULL;
    }
}

/*Creation of the hypergraph and the grail index*/
void GrailIndex::buildGrailIndex() {
    createHyperGraph();

    Garray<uint32_t> dfs_stack;
    // cout << str_components_.getSccNumber() << endl;
    // index_.init(graph_.getNodes('S'));
    // cout << index_.getSize() << endl;

    Vertex *vertices = new Vertex[graph_.getNodes('S')];
    assert(vertices != NULL);
    index_ = new Garray<uint32_t>[graph_.getNodes('S')];
    assert(index_ != NULL);

    srand((unsigned) time(NULL));

    for (uint32_t i = 0; i < graph_.getNodes('S'); i++) {
        Garray<uint32_t> &neighbors = graph_.getNeighbors(i, 'S');
        vertices[i].total = neighbors.getElements();
        vertices[i].neighbors = new uint32_t[vertices[i].total];
        memcpy(vertices[i].neighbors, neighbors.retVal(), vertices[i].total * sizeof(uint32_t));
    }


    uint32_t order = 1, index = 0;
    for (uint32_t i = 0; i < graph_.getNodes('S'); i++) {
        if (vertices[i].visited == false)
            postOrderTraversal(i, vertices, dfs_stack, order, index);
    }

    for (uint32_t i = 0; i < graph_.getNodes('S'); i++) {
        vertices[i].childrenvisited = 0;
        vertices[i].visited = false;
    }

    // order = 1;
    // index = 2;
    // uint32_t start = graph_.getNodes('S');
    // uint32_t i = rand() % start;
    // postOrderTraversal(i, vertices, dfs_stack, order, index);
    // for (uint32_t i = 0; i < start; i++) {
    //     if (vertices[i].visited == false)
    //         postOrderTraversal(i, vertices, dfs_stack, order, index);
    // }
    //
    // for (uint32_t i = 0; i < graph_.getNodes('S'); i++) {
    //     vertices[i].childrenvisited = 0;
    //     vertices[i].visited = false;
    // }
    //
    // order = 1;
    // index = 4;
    // i = rand() % start;
    // postOrderTraversal(i, vertices, dfs_stack, order, index);
    // for (uint32_t i = 0; i < start; i++) {
    //     if (vertices[i].visited == false)
    //         postOrderTraversal(i, vertices, dfs_stack, order, index);
    // }


    delete[] vertices;
    vertices = NULL;

    // // graph_.print();
    // for (uint32_t i = 0; i < graph_.getNodes('S'); i++)
    //     index_[i].print();
}

/*Given the set of strongly connected components, creates the hypergraph
 *of the initial graph, which is stored in the same Graph structure, as
 *the initial
 */
void GrailIndex::createHyperGraph() {
    graph_.initSccHypergraph(str_components_.getSccNumber());
    str_components_.addSccNeighbors();
}


void GrailIndex::postOrderTraversal(const uint32_t &node, Vertex *vertices, Garray<uint32_t> &dfs_stack, uint32_t &order, uint32_t &index) {
    uint32_t v, w;

    dfs_stack.enstack(node);

    while (dfs_stack.isEmpty() == false) {
        v = dfs_stack.top();
        if (vertices[v].visited == false) {
            vertices[v].visited = true;
            if (vertices[v].total == 0) {
                v = dfs_stack.popBack();
                // if (v >= graph_.getNodes('S'))
                //     cout << "v sucks" << v << endl;
                Garray<uint32_t> &val_array = index_[v];
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
                Garray<uint32_t> &val_array = index_[w];
                if (minrank == -1)
                    minrank = val_array[index];
                else {
                    minrank = (val_array[index] < minrank) ? val_array[index] : minrank;
                }
            }

            Garray<uint32_t> &val_array = index_[v];
            val_array.enstack(minrank);
            val_array.enstack(order);
            ++order;
        }
    }

    dfs_stack.clear();
}

GRAIL_ANSWER GrailIndex::isReachableGrailIndex(uint32_t source_node, uint32_t target_node) {
    uint32_t id1 = str_components_.findNodeStronglyConnectedComponentID(source_node);
    uint32_t id2 = str_components_.findNodeStronglyConnectedComponentID(target_node);

    if (!subset(index_[id2][0], index_[id2][1], index_[id1][0], index_[id1][1]))
        return NO;
    else return MAYBE;
    /*if (!subset(index_[id2][2], index_[id2][3], index_[id1][2], index_[id1][3]))
        return NO;
    if (!subset(index_[id2][4], index_[id2][5], index_[id1][4], index_[id1][5]))
        return NO;*/
}
