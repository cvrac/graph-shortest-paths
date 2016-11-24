#include "SCC.hpp"

#include <iostream>
#include <assert.h>

using namespace std;

SCC::Component::Component(uint32_t &id) : component_id(id),
 included_nodes_count(32), included_node_ids(included_nodes_count) {
     included_nodes_count = 0;
 }

SCC::Component::Component() : component_id(0), included_nodes_count(32),
included_node_ids(included_nodes_count) {
    included_nodes_count = 0;
}

SCC::Component::~Component() { }

SCC::SCC(const uint32_t &size, Graph &prgraph) : graph(prgraph), components_(size),
    components_count_(0), inverted_index_size_(0),
    id_belongs_to_component_(NULL) { }

SCC::~SCC() { }

void SCC::init() {
    inverted_index_size_ = graph.getNodes();
    id_belongs_to_component_ = new uint32_t[inverted_index_size_];
}

//SCC estimation, on the given static graph, using Tarjan's algorithm
void SCC::estimateStronglyConnectedComponents() {
    this->tarjanAlgorithm();
}

/*Iterative implementation of Tarjan's algorithm*\
*/
void SCC::tarjanAlgorithm() {
    uint32_t index = 0;
    Garray<uint32_t> tarj_stack;
    Vertex *vertices = new Vertex[graph.getNodes()];
    HashTable<uint32_t> visited(253);
    NodeIndex::ListHead *node = NULL;
    // cout << "ni" << endl;
    for (uint32_t i = 0; i < graph.getNodes(); i++) {
        if ((node = graph.outer_index_.getListHead(i)) != NULL) {
            // cout << "node = " << i << endl;
            tarj_stack.clear();
            if (visited.searchInsert(i))
                stronglyConnected(i, tarj_stack, visited, vertices, &index);
        }
    }
    // for (int i = 0; i < graph.getNodes(); i++)
        // cout << vertices[i].node_id_ << " " << vertices[i].index_ << " " << vertices[i].lowlink_ << endl;
    delete[] vertices;
    vertices = NULL;
}

void SCC::stronglyConnected(uint32_t &node, Garray<uint32_t> &tarj_stack, HashTable<uint32_t> &visited, Vertex *vertices, uint32_t *index) {
    uint32_t v, tempId;
    // cout << "-----------" << endl;
    // cout << node << endl;
    vertices[node].index_ = *index;
    vertices[node].lowlink_ = *index;
    // cout << vertices[node].index_ << " " << vertices[node].lowlink_ << endl;
    // cout << "-----------" << endl;
    ++(*index);
    tarj_stack.enstack(node);
    vertices[node].onStack = true;
    // if (node == 5)
    //     cout << vertices[node].lowlink_;

    // vertices[node].parent_id_ = node;
    Garray<uint32_t> &neighbors = graph.getNeighbors(node, 'F');
    for (int i = 0; i < neighbors.getElements(); i++) {
        tempId = neighbors[i];
        if (visited.searchInsert(tempId)) {
            stronglyConnected(tempId, tarj_stack, visited, vertices, index);
            vertices[node].lowlink_ = (vertices[node].lowlink_ < vertices[tempId].lowlink_) ? vertices[node].lowlink_ : vertices[tempId].lowlink_;
            // cout << "node = " << node << endl;
            // cout << vertices[node].index_ << " " << vertices[node].lowlink_ << endl;
        }
        if (vertices[tempId].onStack == true)
            vertices[node].lowlink_ = (vertices[node].lowlink_ < vertices[tempId].index_ ) ? vertices[node].lowlink_ : vertices[tempId].index_;
    }

    if (vertices[node].lowlink_ == vertices[node].index_) {
        // cout << node << endl;
        Component &comp = components_[components_count_];
        do {
            tempId = tarj_stack.popBack();
            vertices[tempId].onStack = false;
            comp.included_node_ids.enstack(tempId);
            ++comp.included_nodes_count;
            id_belongs_to_component_[tempId] = components_count_;
        } while (tempId != node);
        ++components_count_;
    }

    // while (!dfs_stack.isEmpty()) {
    //     v = dfs_stack.popBack();
    //     cout << v << endl;
    //     if (visited.searchInsert(v)) {
    //         vertices[v].node_id_ = v;
    //         vertices[v].index_ = *index;
    //         vertices[v].lowlink_ = *index;
    //         ++(*index);
    //         tarj_stack.enstack(v);
    //         vertices[v].onStack = true;
    //
    //         Garray<uint32_t> &neighbors = graph.getNeighbors(v, 'F');
    //         for (int i = 0; i < neighbors.getElements(); i++) {
    //             tempId = neighbors[i];
    //             if (!visited.search(tempId))
    //                 dfs_stack.enstack(tempId);
    //         }
    //     }
    // }
    // uint32_t v, tempId;
    // dfs_stack.enstack(node);
    // vertices[node].parent_id_ = node;
    // while (!dfs_stack.isEmpty()) {
    //     v = dfs_stack.popBack();
    //     // cout << "v = " << v << endl;
    //     if (!visited.search(v)) {
    //         visited.insert(v);
    //         vertices[v].node_id_ = v;
    //         vertices[v].index_ = *index;
    //         vertices[v].lowlink_ = *index;
    //         ++(*index);
    //         tarj_stack.enstack(v);
    //         vertices[v].onStack = true;
    //
    //         Garray<uint32_t> &neighbors = graph.getNeighbors(v, 'F');
    //         for (int i = 0; i < neighbors.getElements(); i++) {
    //             tempId = neighbors[i];
    //             if (!visited.search(tempId)) {
    //                 dfs_stack.enstack(tempId);
    //                 // tarj_stack.enstack(tempId);
    //                 vertices[tempId].node_id_ = tempId;
    //                 vertices[tempId].parent_id_ = v;
    //                 // cout << vertices[tempId].node_id_ << endl;
    //             } else if (vertices[tempId].onStack == true) {
    //                 vertices[v].lowlink_ = (vertices[v].lowlink_ < vertices[tempId].index_) ? vertices[v].lowlink_ : vertices[tempId].index_;
    //             }
    //         }
    //     }
    //     // if (v != node)
    //     vertices[vertices[v].parent_id_].lowlink_ = (vertices[vertices[v].parent_id_].lowlink_ < vertices[v].lowlink_) ? vertices[vertices[v].parent_id_].lowlink_ : vertices[v].lowlink_;
    //     // tarj_stack.print();
    //     // cout << "foo" << endl;
    //     if (vertices[v].lowlink_ == vertices[v].index_) {
    //         Component &comp = components_[components_count_];
    //         // tempId = tarj_stack.popBack();
    //         // cout << v << endl;
    //         do {
    //             tempId = tarj_stack.popBack();
    //             vertices[tempId].onStack = false;
    //             comp.included_node_ids.enstack(tempId);
    //             ++comp.included_nodes_count;
    //             id_belongs_to_component_[tempId] = components_count_;
    //             // cout << "not same" << endl;
    //         } while (tempId != v);
    //         ++components_count_;
    //     }
    //
    // }
    //
    //
    // dfs_stack.clear();
    // tarj_stack.clear();
    // visited.clear();
}

void SCC::print() {
    for (int i = 0; i < components_count_; i++) {
        cout << "Component " << i << endl;
        for (int j = 0; j < components_[i].included_nodes_count; j++)
            cout << components_[i].included_node_ids[j] << " ";
        cout << "-------------------------------" << endl;
    }
}
