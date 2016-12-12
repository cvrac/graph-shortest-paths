#include "GrailIndex.hpp"

#include <iostream>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

GrailIndex::GrailIndex(Graph &gr, SCC &components) : run(2), use(true), graph_(gr), str_components_(components) { }

GrailIndex::~GrailIndex() { }

/*Creation of the hypergraph and the grail index*/
void GrailIndex::buildGrailIndex() {
    uint32_t total_scc = str_components_.getSccNumber();
    uint32_t total_nodes = graph_.getNodes('N');

    if (total_scc == total_nodes) {
        use = false;
        buildGrailIndex('F');
        buildGrailIndex('B');
    } else {
        clock_t start = clock();
        createHyperGraph();
//        cout << "Hypergraph:: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
        buildGrailIndex('R');
        buildGrailIndex('L');
    }
}

void GrailIndex::buildGrailIndex(const char &dir) {
    uint32_t end = graph_.getNodes('S');
    if (use == false)
        end = graph_.getNodes('N');
    Garray<Garray<uint32_t> > &scc_index = (dir == 'R' || dir == 'F' ? outer_index_ : inner_index_);
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
        if (index == 0)
            root = 0;
        else
            root = rand() % end;
        postOrderTraversal(root, vertices, dfs_stack, order, index, dir);
        for (uint32_t i = 0; i < end; i++) {
            if (graph_.checkVisitedNode(i, dir, index + 1) == false)
                postOrderTraversal(i, vertices, dfs_stack, order, index, dir);
        }
        // for (uint32_t i = 0; i < end; i++) {
        //     vertices[i].childrenvisited = 0;
        //     vertices[i].visited = false;
        // }
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

/*Post order traversal of the graph, for the creation of the grail index.
 *Two indices are created, one forward, and one backwards
 */
void GrailIndex::postOrderTraversal(const uint32_t &node, Garray<Vertex> &vertices, Garray<uint32_t> &dfs_stack, uint32_t &order, uint32_t &index, const char &dir) {
    uint32_t v, w;
    Garray<Garray<uint32_t> > &scc_index = (dir == 'R' || dir == 'F' ? outer_index_ : inner_index_);
    dfs_stack.enstack(node);

    while (dfs_stack.isEmpty() == false) {
        v = dfs_stack.top();
        if (graph_.checkMarkVisitedNode(v, dir, index + 1)) {
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
            if (graph_.checkVisitedNode(w, dir, index + 1) == false && w != v)
                dfs_stack.enstack(w);
            ++vertices[v].childrenvisited;
        } else {
            v = dfs_stack.popBack();
            long minrank = -1;

            for (uint32_t i = 0; i < vertices[v].total; i++) {
                w = vertices[v].neighbors[i];
                if (w == v) continue;
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
            vertices[v].childrenvisited = 0;
        }
    }

    dfs_stack.clear();
}

/*Grail reachability query*/
GRAIL_ANSWER GrailIndex::isReachableGrailIndex(uint32_t source_node, uint32_t target_node, const char &dir) {
    Garray<Garray<uint32_t> > &scc_index = (dir == 'R' ? outer_index_ : inner_index_);
    uint32_t id1 = str_components_.findNodeStronglyConnectedComponentID(source_node);
    uint32_t id2 = str_components_.findNodeStronglyConnectedComponentID(target_node);

    if (use == false) {
        id1 = source_node;
        id2 = target_node;
    }

    for (uint32_t index = 0; index < run; index += 2) {
        if (!subset(scc_index[id2][index], scc_index[id2][index + 1], scc_index[id1][index], scc_index[id1][index + 1]))
            return NO;
    }
    return MAYBE;
}
