#include "GrailIndex.hpp"

#include <iostream>
#include <stdint.h>

GrailIndex::GrailIndex(Graph &gr, SCC &components) : graph_(gr), str_components_(components)
{ }

GrailIndex::~GrailIndex() { }

void GrailIndex::buildGrailIndex() {
    createHyperGraph();
    // postOrderTraversal();
    // index_.init(str_components_.getElements);
    // Garray<uint32_t> dfs_stack;
    // Vertex *vertices = new Vertex[str_components_.getElements()];
    //
    // for (uint32_t i = 0; i < graph.getNodes(); i++) {
    //     Garray<uint32_t> &neighbors = graph.getNeighbors(i, 'F');
    //     vertices[i].total = neighbors.getElements();
    //     vertices[i].neighbors = new uint32_t[vertices[i].total];
    //     memcpy(vertices[i].neighbors, neighbors.retVal(), vertices[i].total * sizeof(uint32_t));
    // }
    //
    // for (uint32_t i = 0; i < str_components_.getElements(); i++) {
    //     if (!visited[i])
    //         postOrderTraversal(i, visited, dfs_stack);
    // }
}

/*Given the set of strongly connected components, creates the hypergraph
 *of the initial graph, which is stored in the same Graph structure, as
 *the initial
 */
void GrailIndex::createHyperGraph() {
    graph_.initSccHypergraph(str_components_.getSccNumber());
    str_components_.addSccNeighbors();
}


void GrailIndex::postOrderTraversal(const uint32_t &node, Vertex *vertices, Garray<uint32_t> & dfs_stack) {
    // uint32_t v;
    //
    // dfs_stack.enstack(node);
    //
    // while (dfs_stack.isEmpty() == false) {
    //     v = dfs_stack.top();
    //     if (!visited[v])
    // }
}
