#include "OperationsControl.hpp"

#include <string>
#include <iostream>

#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iomanip>

using namespace std;
bool flag = false;
OperationsControl::OperationsControl(const float &cc_threshold, const uint8_t pool_size) :
 paths_(pool_size),  strongly_conn_(graph_),
 connected_components_(graph_, cc_threshold), grail_index_(graph_, strongly_conn_),
 res_array_(40), scheduler_(pool_size, res_array_) {

     for (uint32_t i = 0; i < pool_size; i++)
        paths_[i] = new ShortestPath(graph_, strongly_conn_, grail_index_);

}

OperationsControl::~OperationsControl() {
    // for (uint32_t i = 0; i < paths_.getElements(); i++)
    //     delete[] paths_[i];
}

void OperationsControl::run(const char &mode) {
   clock_t start = clock();
    this->buildGraph(mode);
//    cout << "Threshold " << connected_components_.getThreshold() << endl;
   // cout << "buildGraph: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
//    start = clock();
    if (mode == 'c') {
        connected_components_.estimateConnectedComponents();
//        cout << "estimateConnectedComponents: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
        //connected_components_.print();
    }
    if (mode == 's') {
        start = clock();
        this->strongly_conn_.init();
        this->strongly_conn_.estimateStronglyConnectedComponents();
//        cout << "SCC: " << (clock() - start) / (double) CLOCKS_PER_SEC << "\n";
        //this->strongly_conn_.print();
        start = clock();
        this->grail_index_.buildGrailIndex();
//        cout << "Hypergraph and grail build: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
        //graph_.print();
    }
    //start = clock();
    this->runQueries(mode);
    //cout << "runQueries: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
    cout << "Total swaps: " << graph_.Graph::swaps_ << endl;
}

void OperationsControl::parseNodeIds(uint32_t *source, uint32_t *target) {
    uint32_t sourceNode = *source;
    int ch;
    while (ch != ' ' && ch != '\t') {
        if (ch >= '0' && ch <= '9') {
            sourceNode = sourceNode * 10 + (ch - '0');
        }
        ch = getchar();
    }
    // cout << sourceNode << endl;
    while ((ch = getchar()) == ' ' || ch == '\t')
        continue;

    uint32_t targetNode = 0;
    while (ch != '\n') {
        if (ch >= '0' && ch <= '9') {
            targetNode = targetNode * 10 + (ch - '0');
        }
        ch = getchar();
    }

    *source = sourceNode;
    *target = targetNode;
}

void OperationsControl::buildGraph(const char &mode) {
    int ch;
    uint32_t sourceNode, targetNode;
    char cLine[100];
    int cLineSize = sizeof(cLine);

    // fgets(cLine, cLineSize, stdin);

    // if (!strcmp)

    while ((ch = getchar()) != EOF && ch != 'S') {
        sourceNode = ch - '0';
        parseNodeIds(&sourceNode, &targetNode);
        // cout << sourceNode << " " << targetNode << endl;
        graph_.insertEdge(sourceNode, targetNode, 'N');
    }
}

void OperationsControl::runQueries(const char &mode) {
    paths_[0]->init(); // Do for every ShortestPath object
    bool bidirectional_insert = (mode == 'c');
    uint32_t search_skips = 0, sourceNode, targetNode;
    //uint32_t searches = 0;
    double total_rebuilding_time = 0;
    double total_query_time = 0;
    char cLine[100];
    char cLineSize = sizeof(cLine);
    // uint32_t size = 60;
    // uint32_t *batch = new uint32_t[size];
    // uint32_t counter = 0;
    //clock_t start = clock();
    int ch;

    while ((ch = getchar()) == '\n') continue;
    while ((ch = getchar()) != '\n') continue;

    while ((ch = getchar()) != EOF) {

        if (ch == 'F') {
            if (mode == 'c') {
                if (connected_components_.needRebuilding()) {
//                    clock_t start = clock();
                    connected_components_.rebuildIndexes();
//                    cout << "Rebuilding time: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
                    //total_rebuilding_time += (clock() - start) / (double) CLOCKS_PER_SEC;
                }
                connected_components_.setQueriesCount(0);
                connected_components_.setUpdateIndexUseCount(0);
            }
            // cout << "here" << endl;
        } else if (ch == 'Q') {
            ch = getchar();
            ch = getchar();
            sourceNode = ch - '0';
            parseNodeIds(&sourceNode, &targetNode);

            uint32_t total_nodes = graph_.getNodes('N');
            if (sourceNode >= total_nodes || targetNode >= total_nodes) {
                cout << -1 << "\n";
                continue;
            }

            // cout << sourceNode << " " << targetNode << endl;

            if (mode == 's') {
                cout << this->estimateShortestPathStronglyConnected(sourceNode, targetNode) << "\n";
            } else if (mode == 'c') {
                if (connected_components_.sameConnectedComponent(sourceNode, targetNode)) {
                    //searches++;
                    cout << this->estimateShortestPath(sourceNode, targetNode) << "\n";
                }
                else {
                    search_skips++;
                    cout << -1 << "\n";
                }
            } else if (mode == 'n') {
                cout << this->estimateShortestPath(sourceNode, targetNode) << "\n";
            }

        } else if (ch == 'A') {

            ch = getchar();
            ch = getchar();
            sourceNode = ch - '0';
            parseNodeIds(&sourceNode, &targetNode);

            if (graph_.insertEdge(sourceNode, targetNode, 'N') && mode == 'c') {
                connected_components_.insertNewEdge(sourceNode, targetNode);
            }
        }
    }
//    cout << "Search skips: " << search_skips << endl;
}

inline int OperationsControl::estimateShortestPath(uint32_t &source, uint32_t &target) {
    int ret = paths_[0]->shortestPath(source, target, 'A');
    paths_[0]->reset();
    return ret;
}

inline int OperationsControl::estimateShortestPathStronglyConnected(uint32_t &source, uint32_t &target) {
    int ret = -1;
    if (strongly_conn_.findNodeStronglyConnectedComponentID(source) == strongly_conn_.findNodeStronglyConnectedComponentID(target))
        ret = paths_[0]->shortestPath(source, target, 'S');
    else if (strongly_conn_.findNodeStronglyConnectedComponentID(target) > strongly_conn_.findNodeStronglyConnectedComponentID(source))
        ret = -2;

    if (ret > -1) {
        paths_[0]->reset();
        return ret;
    } else if (ret == -2)
        return -1;

    enum GRAIL_ANSWER grail_ans;
    if ((grail_ans = grail_index_.isReachableGrailIndex(source, target, 'R')) == NO || (grail_ans = grail_index_.isReachableGrailIndex(target, source, 'L')) == NO) {
        return -1;
    } else if (grail_ans == MAYBE) {
        ret = paths_[0]->shortestPath(source, target, 'G'); //part1 ektelesi opou mesa emperiextai kai grail
        paths_[0]->reset();
        return ret;
    }
}
