#include "SCC.hpp"

#include <iostream>
#include <assert.h>

using namespace std;

SCC::Component::Component(uint32_t &id) : component_id(id),
                                          included_nodes_count(0) {
    //  included_nodes_count = 0;
}

SCC::Component::Component() : component_id(0), included_nodes_count(0) {
    // included_nodes_count = 0;
}

SCC::Component::~Component() { }

SCC::SCC(const uint32_t &size, Graph &prgraph, ShortestPath &pathz) : graph(prgraph), path(pathz),
                                                                      components_(size), components_count_(0), inverted_index_size_(0),
                                                                      id_belongs_to_component_(NULL) { }

SCC::~SCC() {
    delete[] id_belongs_to_component_;
    id_belongs_to_component_ = NULL;
}

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
    Garray<uint32_t> dfs_stack;
    Vertex *vertices = new Vertex[graph.getNodes()];
    // HashTable<uint32_t> visited(100003);
    components_.increaseSize(graph.getNodes());
    NodeIndex::ListHead *node = NULL;

/*    for (uint32_t i = 0; i < graph.getNodes(); i++) {
        Garray<uint32_t> &neighbors = graph.getNeighbors(i, 'F');
        vertices[i].total = neighbors.getElements();
        vertices[i].neighbors = new uint32_t[vertices[i].total];
        memcpy(vertices[i].neighbors, neighbors.retVal(), vertices[i].total * sizeof(uint32_t));
    }
*/
    for (uint32_t i = 0; i < graph.getNodes(); i++) {
        if ((node = graph.outer_index_.getListHead(i)) != NULL) {
            if (vertices[i].visited == false)
                stronglyConnected(i, dfs_stack, tarj_stack, vertices, &index);
            // if (!visited.search(i))
        }
    }

    /*  for (uint32_t i = 0; i < graph.getNodes(); i++) {
          delete[] vertices[i].neighbors;
          vertices[i].neighbors = NULL;
      }
  */
    delete[] vertices;
    vertices = NULL;
}

// // void SCC::stronglyConnected(uint32_t &node, Garray<uint32_t> &tarj_stack, HashTable<uint32_t> &visited, Vertex *vertices, uint32_t *index) {
// //     uint32_t v = node, tempId;
// //     vertices[v].index_ = *index;
// //     vertices[v].lowlink_ = *index;
// //     ++(*index);
// //     vertices[v].last_neighbor_ = 0;
// //     vertices[v].parent_id_ = v;
// //     vertices[v].onStack = true;
// //     tarj_stack.enstack(v);
// //     while (true) {
// //         if (vertices[v].last_neighbor_ < vertices[v].total) {
// //             tempId = vertices[v].neighbors[vertices[v].last_neighbor_];
// //             ++vertices[v].last_neighbor_;
// //             if (visited.searchInsert(tempId)) {
// //                 vertices[tempId].node_id_ = tempId;
// //                 vertices[tempId].index_ = *index;
// //                 vertices[tempId].lowlink_ = *index;
// //                 vertices[tempId].parent_id_ = v;
// //                 ++(*index);
// //                 tarj_stack.enstack(tempId);
// //                 vertices[tempId].onStack = true;
// //                 v = tempId;
// //             } else if (vertices[tempId].onStack == true) {
// //                 vertices[v].lowlink_ = (vertices[v].lowlink_ < vertices[tempId].index_)
//                     ? vertices[v].lowlink_ : vertices[tempId].index_;
//             }
//         } else {
//             if (vertices[v].lowlink_ == vertices[v].index_) {
//                 Component &comp = components_[components_count_];
//                 do {
//                     tempId = tarj_stack.popBack();
//                     vertices[tempId].onStack = false;
//                     comp.included_node_ids.enstack(tempId);
//                     ++comp.included_nodes_count;
//                     id_belongs_to_component_[tempId] = components_count_;
//                 } while (tempId != v);
//                 ++components_count_;
//             }
//             uint32_t parent_id_ = vertices[v].parent_id_;
//             if (parent_id_ != v) {
//                 vertices[parent_id_].lowlink_ = (vertices[parent_id_].lowlink_ < vertices[v].lowlink_)
//                     ? vertices[parent_id_].lowlink_ : vertices[v].lowlink_;
//             }
//         }
//     }
//
//     tarj_stack.clear();
//

void SCC::stronglyConnected(uint32_t &node, Garray<uint32_t> &dfs_stack, Garray<uint32_t> &tarj_stack, Vertex *vertices, uint32_t *index) {

    uint32_t v, w, tempId;
    dfs_stack.enstack(node);

    while (dfs_stack.isEmpty() == false) {
        v = dfs_stack.top();
        // cout << dfs_stack.getElements() << endl;
        // cout << graph.getNodes() << endl;
        // cout << "v = " << v << endl;
        // cout << "parent = " << vertices[v].parent_id_ << endl;
        // cout << "children visited parent = " << vertices[vertices[v].parent_id_].childrenvisited << " total " << vertices[vertices[v].parent_id_].total << endl;
        if (vertices[v].visited == false) {
            vertices[v].visited = true;
            vertices[v].index_ = *index;
            vertices[v].lowlink_ = *index;
            ++(*index);
            tarj_stack.enstack(v);
            vertices[v].onStack = true;

            Garray<uint32_t> &neighbors = graph.getNeighbors(v, 'F');
            vertices[v].total = neighbors.getElements();
            for (uint32_t i = 0; i < vertices[v].total; i++) {
                w = neighbors[i];
                // cout << "w = " << w << endl;
                if (vertices[w].visited == false) {
                    vertices[w].parent_id_ = v;
                    ++vertices[v].childrenvisited;
                    dfs_stack.enstack(w);
                    // cout << w << " not visited" << endl;
                } else if (vertices[w].onStack == true) {
                    vertices[v].lowlink_ = (vertices[v].lowlink_ < vertices[w].index_)
                                           ? vertices[v].lowlink_ : vertices[w].index_;
                    ++vertices[v].childrenvisited;
                    // cout << w << " visited " << endl;
                } else if (vertices[w].visited == true) {
                    // cout << w << " visited " << endl;
                    ++vertices[v].childrenvisited;
                }
            }
        } else {
            v = dfs_stack.popBack();
            if (vertices[v].childrenvisited == vertices[v].total) {
                if (vertices[v].lowlink_ == vertices[v].index_) {
                    Component &comp = components_[components_count_];
                    do {
                        tempId = tarj_stack.popBack();
                        vertices[tempId].onStack = false;
                        comp.included_node_ids.enstack(tempId);
                        ++comp.included_nodes_count;
                        id_belongs_to_component_[tempId] = components_count_;
                    } while (tempId != v);
                    ++components_count_;
                }
                uint32_t parent_id_ = vertices[v].parent_id_;
                if (parent_id_ != v) {
                    vertices[parent_id_].lowlink_ = (vertices[parent_id_].lowlink_ < vertices[v].lowlink_)
                                                    ? vertices[parent_id_].lowlink_ : vertices[v].lowlink_;
                }
            }


        }

    }

    dfs_stack.clear();
    tarj_stack.clear();
}




int SCC::findNodeStronglyConnectedComponentID(uint32_t &node_id) {
    return id_belongs_to_component_[node_id];
}

int SCC::estimateShortestPathStronglyConnectedComponents(uint32_t &source, uint32_t &target) {
    return (id_belongs_to_component_[source] == id_belongs_to_component_[target]) ? path.shortestPath(source, target, 'S') : -1;
}

void SCC::print() {
    for (int i = 0; i < components_count_; i++) {
        cout << "Component " << i << endl;
        components_[i].included_node_ids.print();
        cout << "-------------------------------" << endl;
    }
}

// SCC::Component& SCC::Component::operator=(const SCC::Component& other) {
//   if (this != &other) {
//       this->component_id = other.component_id;
//       this->included_nodes_count = other.included_nodes_count;
//       memcpy(&this->included_node_ids, &other.included_node_ids, included_nodes_count * sizeof(Garray<uint32_t>));
//   }
//   return *this;
// }
