#include "SCC.hh"

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

SCC::SCC(Graph &prgraph) : graph(prgraph), neighbors_(INITIAL_NEIGHBORS_ARRAY_SIZE) { }

SCC::~SCC() {}

void SCC::init() {
    uint32_t total_nodes = graph.getNodes('N');
    id_belongs_to_component_.init(total_nodes);
    id_belongs_to_component_.setElements(total_nodes);
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
    Garray<Vertex> vertices(graph.getNodes('N'));
    components_.init(graph.getNodes('N'));

    for (uint32_t i = 0; i < graph.getNodes('N'); i++) {
        graph.getNeighbors(i, 'F', 0, neighbors_);
        vertices[i].total = neighbors_.getElements();
        vertices[i].neighbors = new uint32_t[vertices[i].total];
        memcpy(vertices[i].neighbors, neighbors_.retVal(), vertices[i].total * sizeof(uint32_t));
    }

    for (uint32_t i = 0; i < graph.getNodes('N'); i++) {
        if (vertices[i].visited == false)
            stronglyConnected(i, dfs_stack, tarj_stack, vertices, &index);
    }
    components_.shrink(components_.getElements());
}


/*For a given node as a root, calculates the strongly connected components on the paths from it
 *Use of vertices array index, where info for each vertex is stored
 *For the non-recursive implementation, we need a stack to keep the current path
 *A vertex ain't poped from the stack, until the exploration of its children etc has finished, and
 *when this happens, we check whether there has been formatted a new SCC
 */
void SCC::stronglyConnected(uint32_t &node, Garray<uint32_t> &dfs_stack, Garray<uint32_t> &tarj_stack, Garray<Vertex> &vertices, uint32_t *index) {

    uint32_t v, w, tempId;
    uint32_t components_count = components_.getElements();
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
            // w = graph.getNeighbor(v, vertices[v].childrenvisited, 'F');
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
                    Component &comp = components_[components_count];
                    do {
                        tempId = tarj_stack.popBack();
                        vertices[tempId].onStack = false;
                        comp.included_node_ids.enstack(tempId);
                        ++comp.included_nodes_count;
                        id_belongs_to_component_[tempId] = components_count;
                    } while (tempId != v);
                    ++components_count;
                }
                uint32_t parent_id_ = vertices[v].parent_id_;
                if (parent_id_ != v) {
                    vertices[parent_id_].lowlink_ = (vertices[parent_id_].lowlink_ < vertices[v].lowlink_)
                        ? vertices[parent_id_].lowlink_ : vertices[v].lowlink_;
                }
            }


        }

    }
    components_.setElements(components_count);
    dfs_stack.clear();
    tarj_stack.clear();
}

// int SCC::estimateShortestPathStronglyConnectedComponents(uint32_t &source, uint32_t &target) {
//     if (id_belongs_to_component_[source] == id_belongs_to_component_[target])
//         return path.shortestPath(source, target, 'S');
//     else if (id_belongs_to_component_[target] > id_belongs_to_component_[source])
//         return -2;
//     return -1;
// }

void SCC::addSccNeighbors() {
    uint32_t neighborScc, edgeCounter = 0, scc;

    // for (uint32_t comp = 0; comp < components_.getElements(); comp++) {
    //     Component &scc = components_[comp];
    //     for (uint32_t vertex = 0; vertex < scc.included_nodes_count; vertex++) {
    //         Garray<uint32_t> &neighbors_ = graph.getNeighbors(scc.included_node_ids[vertex], 'F');
    //         for (uint32_t neighbor = 0; neighbor < neighbors_.getElements(); neighbor++) {
    //             neighborScc = id_belongs_to_component_[neighbors_[neighbor]];
    //             if (neighborScc == comp) continue;
    //             if (graph.insertEdge(comp, neighborScc, 'S'))
    //                 ++edgeCounter;
    //         }
    //     }
    // }

    for (uint32_t vertex = 0; vertex < graph.getNodes('N'); vertex++) {
        scc = id_belongs_to_component_[vertex];
        graph.getNeighbors(vertex, 'F', 0, neighbors_);
        for (uint32_t i = 0; i < neighbors_.getElements(); i++) {
            neighborScc = id_belongs_to_component_[neighbors_[i]];
            if (neighborScc == scc) continue;
            if (graph.insertEdge(scc, neighborScc, 'S', 0))
                ++edgeCounter;
        }
    }

}

void SCC::iterateStronglyConnectedComponentID(ComponentCursor *cursor) {
    if (cursor == NULL) {
        return;
    }
    cursor->next = 0;
}

bool SCC::nextStronglyConnectedComponentID(ComponentCursor *cursor) {
    if (cursor == NULL || cursor->next++ >= components_.getElements()) {
        return false;
    }
    cursor->component_ptr_ = &components_[cursor->next-1];
    return true;
}

void SCC::print() {
/*    for (int i = 0; i < components_.getElements(); i++) {
        cout << "Component " << i << "\n";
        components_[i].included_node_ids.print();
        cout << "-------------------------------" << "\n";
    }
*/
    ComponentCursor cursor;
    this->iterateStronglyConnectedComponentID(&cursor);
    while (this->nextStronglyConnectedComponentID(&cursor)) {
        cout << "Component " << cursor.next-1 << "\n";
        cursor.component_ptr_->included_node_ids.print();
        cout << "-------------------------------" << "\n";
    }

    for (int i = 0 ; i < id_belongs_to_component_.getElements() ; i++) {
        cout << "inverted_index[" << i << "] = " << id_belongs_to_component_[i] << "\n";
    }
}
