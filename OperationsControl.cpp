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
OperationsControl::OperationsControl(uint32_t &hashSize, const float &cc_threshold) : path_(graph_, strongly_conn_),
 strongly_conn_(hashSize, graph_, path_), connected_components_(graph_, cc_threshold) { }

OperationsControl::~OperationsControl() { }

void OperationsControl::run(const char &mode) {
    clock_t start = clock();
    this->buildGraph(mode);
//    cout << "Threshold " << connected_components_.getThreshold() << endl;
//    cout << "buildGraph: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
    start = clock();
    if (mode == 'c') {
        connected_components_.estimateConnectedComponents();
//        cout << "estimateConnectedComponents: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
        //connected_components_.print();
    }
    if (mode == 's') {
        this->strongly_conn_.init();
        this->strongly_conn_.estimateStronglyConnectedComponents();
    }
    //start = clock();
    this->runQueries(mode);
    //cout << "runQueries: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
    // if (mode == 's') {
    //     this->strongly_conn_.print();
    // }
}

void OperationsControl::buildGraph(const char &mode) {
    string line;
    char cLine[100];
    //bool bidirectional_insert = (mode == 'c');
    while (getline(cin, line)) {
        strcpy(cLine, line.c_str());
        char *n1;
        n1 = strtok(cLine, " \t\n\0");
        if (n1 == NULL) continue;
        if (n1[0] == 'S' || !strcmp(n1, "STATIC") || !strcmp(n1, "DYNAMIC")) break;
        uint32_t sourceNode = atol(n1);
        char *n2 = strtok(NULL, " \t\n\0");
        if (n2 == NULL) continue;
        uint32_t targetNode = atol(n2);
        graph_.insertEdge(sourceNode, targetNode);
    }
}

void OperationsControl::runQueries(const char &mode) {
    string line;
    char cLine[100];
    //bool bidirectional_insert = (mode == 'c');
    uint32_t search_skips = 0;
    //uint32_t searches = 0;
    double total_rebuilding_time = 0;
    double total_query_time = 0;
    // uint32_t size = 60;
    // uint32_t *batch = new uint32_t[size];
    // uint32_t counter = 0;
    //clock_t start = clock();
    while (getline(cin, line)) { //cout << line << endl;
        strcpy(cLine, line.c_str());
        char *op;
        op = strtok(cLine, " \t\n\0");
        if (op == NULL) continue;
        if (!strcmp(op, "A")) {
            char *node = strtok(NULL, " \t\n\0");
            if (node == NULL) continue;
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \t\n\0");
            if (node == NULL) continue;
            uint32_t targetNode = atol(node);
            if (graph_.insertEdge(sourceNode, targetNode) && mode == 'c') {
                connected_components_.insertNewEdge(sourceNode, targetNode);
            }
            // if (counter == size) {
            //     uint32_t *old = batch;
            //     batch = new uint32_t[size * 2];
            //     memcpy(batch, old, sizeof(uint32_t) * size);
            //     size *= 2;
            //     delete[] old;
            // }
            // batch[counter] = 0;
            // batch[counter + 1] = sourceNode;
            // batch[counter + 2] = targetNode;
            // counter += 3;
            // graph_.insertEdge(sourceNode, targetNode);
        } else if (!strcmp(op, "Q")) {
            clock_t start = clock();
            char *node = strtok(NULL, " \t\n\0");
            if (node == NULL) continue;
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \t\n\0");
            if (node == NULL) continue;
            uint32_t targetNode = atol(node);
            uint32_t total_nodes = graph_.getNodes();
            if (sourceNode >= total_nodes || targetNode >= total_nodes) {
                cout << -1 << "\n";
                continue;
            }

            if (mode == 's') {
                cout << this->estimateShortestPath(sourceNode, targetNode) << endl;
            } else if (mode == 'c') {
                if (connected_components_.sameConnectedComponent(sourceNode, targetNode)) {
                    //searches++;
                    cout << path_.shortestPath(sourceNode, targetNode, 'A') << "\n";
                    path_.reset();
                }
                else {
                    search_skips++;
                    cout << -1 << "\n";
                }
            } else if (mode == 'n') {
                cout << path_.shortestPath(sourceNode, targetNode, 'A') << "\n";
                path_.reset();
            }
            total_query_time += (clock() - start) / (double) CLOCKS_PER_SEC;
            // if (counter == size) {
            //     uint32_t *old = batch;
            //     batch = new uint32_t[size * 2];
            //     memcpy(batch, old, sizeof(uint32_t) * size);
            //     size *= 2;
            //     delete[] old;
            // }
            // batch[counter] = 1;
            // batch[counter + 1] = sourceNode;
            // batch[counter + 2] = targetNode;
            // counter += 3;
        } else if (!strcmp(op, "F")) {
//            cout << "\nQuery time: " << total_query_time << endl;
            total_query_time = 0;
            if (mode == 'c') {
                if (connected_components_.needRebuilding()) {
                    clock_t start = clock();
                    connected_components_.rebuildIndexes();
//                    cout << "Rebuilding time: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
                    //total_rebuilding_time += (clock() - start) / (double) CLOCKS_PER_SEC;
                }
                connected_components_.setQueriesCount(0);
                connected_components_.setUpdateIndexUseCount(0);
            }
            // for (uint32_t i = 0; i < counter; i += 3) {
            //     if (batch[i] == 0) {
            //         graph_.insertEdge(batch[i + 1], batch[i + 2]);
            //     } else {
            //         cout << path_.shortestPath(batch[i + 1], batch[i + 2]) << endl;
            //         path_.reset();
            //     }
            // }
            // counter = 0;
        }
        //connected_components_.print();
    }
    //connected_components_.print();
//    cout << "Search skips: " << search_skips; // << "\nSearches: " << searches << endl;
    //cout << "Total rebuilds: " << connected_components_.getTotalRebuilds() << endl;
    //cout << "Rebulding time: " << total_rebuilding_time << endl;
    //cout << "Pure query time: " << ((clock() - start) / (double) CLOCKS_PER_SEC) - total_rebuilding_time << endl;
    // delete[] batch;
}

int OperationsControl::estimateShortestPath(uint32_t &source, uint32_t &target) {
    int ret = strongly_conn_.estimateShortestPathStronglyConnectedComponents(source, target);
    path_.reset();
    if (ret != -1) {
        cout << "same component " << source << " " << target << endl;
        return ret;
    } else if (ret == -1)
        ret = path_.shortestPath(source, target, 'A');
    path_.reset();
    return ret;
}
