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

    for (uint32_t i = 0; i < graph.getNodes(); i++) {
        Garray<uint32_t> &neighbors = graph.getNeighbors(i, 'F');
        vertices[i].total = neighbors.getElements();
        vertices[i].neighbors = new uint32_t[vertices[i].total];
        memcpy(vertices[i].neighbors, neighbors.retVal(), vertices[i].total * sizeof(uint32_t));
    }

    for (uint32_t i = 0; i < graph.getNodes(); i++) {
        if ((node = graph.outer_index_.getListHead(i)) != NULL) {
            if (vertices[i].visited == false)
                stronglyConnected(i, dfs_stack, tarj_stack, vertices, &index);
        }
    }

  for (uint32_t i = 0; i < graph.getNodes(); i++) {
        delete[] vertices[i].neighbors;
        vertices[i].neighbors = NULL;
    }

    delete[] vertices;
    vertices = NULL;
}


/*For a given node as a root, calculates the strongly connected components on the paths from it
 *Use of vertices array index, where info for each vertex is stored
 *For the non-recursive implementation, we need a stack to keep the current path
 *A vertex ain't poped from the stack, until the exploration of its children etc has finished, and
 *when this happens, we check whether there has been formatted a new SCC
 */
void SCC::stronglyConnected(uint32_t &node, Garray<uint32_t> &dfs_stack, Garray<uint32_t> &tarj_stack, Vertex *vertices, uint32_t *index) {

    uint32_t v, w, tempId;
    dfs_stack.enstack(node);

    while (dfs_stack.isEmpty() == false) {
        v = dfs_stack.top();
        if (vertices[v].visited == false) {
            vertices[v].visited = true;
            vertices[v].index_ = *index;
            vertices[v].lowlink_ = *index;
            ++(*index);
            tarj_stack.enstack(v);
            vertices[v].onStack = true;
        }
        if (vertices[v].childrenvisited < vertices[v].total) {
            w = vertices[v].neighbors[vertices[v].childrenvisited];
            if (vertices[w].visited == false) {
                vertices[w].parent_id_ = v;
                ++vertices[v].childrenvisited;
                dfs_stack.enstack(w);
            } else if (vertices[w].onStack == true) {
                vertices[v].lowlink_ = (vertices[v].lowlink_ < vertices[w].index_)
                    ? vertices[v].lowlink_ : vertices[w].index_;
                ++vertices[v].childrenvisited;
            } else if (vertices[w].visited == true) {
                ++vertices[v].childrenvisited;
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
