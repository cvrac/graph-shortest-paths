#include "GrailIndex.hpp"

#include <iostream>
#include <stdint.h>
#include <assert.h>

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

    for (uint32_t i = 0; i < graph_.getNodes('S'); i++) {
        Garray<uint32_t> &neighbors = graph_.getNeighbors(i, 'S');
        vertices[i].total = neighbors.getElements();
        vertices[i].neighbors = new uint32_t[vertices[i].total];
        memcpy(vertices[i].neighbors, neighbors.retVal(), vertices[i].total * sizeof(uint32_t));
    }


    uint32_t order = 1;
    // cout << "qq2" << endl;
    for (uint32_t i = 0; i < graph_.getNodes('S'); i++) {
        if (vertices[i].visited == false)
            postOrderTraversal(i, vertices, dfs_stack, order);
    }

    delete[] vertices;
    vertices = NULL;

    // graph_.print();
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


void GrailIndex::postOrderTraversal(const uint32_t &node, Vertex *vertices, Garray<uint32_t> &dfs_stack, uint32_t &order) {
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
                    minrank = val_array[0];
                else {
                    minrank = (val_array[0] < minrank) ? val_array[0] : minrank;
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
