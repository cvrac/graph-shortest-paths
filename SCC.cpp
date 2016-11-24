#include "SCC.hpp"

#include <iostream>
#include <assert.h>

using namespace std;

SCC::Component::Component(uint32_t &id) : component_id(id),
 included_nodes_count(32), included_node_ids(included_nodes_count) {
     included_nodes_count = 0;
 }

SCC::Component::~Component() { }

SCC::SCC(const uint32_t &size, Graph &prgraph) : graph(prgraph), components_(size),
    components_count_(0), inverted_index_size_(graph.getNodes()),
    id_belongs_to_component_(inverted_index_size_) { }

SCC::~SCC() { }

//SCC estimation, on the given static graph, using Tarjan's algorithm
void SCC::estimateStronglyConnectedComponents() {
    this->tarjanAlgorithm();
}

/*Iterative implementation of Tarjan's algorithm*\
*/
void SCC::tarjanAlgorithm() {

}
