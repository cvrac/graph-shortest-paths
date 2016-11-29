#include "OperationsControl.hpp"

#include <string>
#include <iostream>

#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iomanip>

bool bidirectional_insert = false; // temp

using namespace std;

OperationsControl::OperationsControl(uint32_t &hashSize) : path_(graph_, hashSize), strongly_conn_(hashSize, graph_), connected_components_(graph_, hashSize) { }

OperationsControl::~OperationsControl() { }

void OperationsControl::run(const uint32_t &hashSize) {
    this->buildGraph();
    //connected_components_.estimateConnectedComponents();
    // this->runQueries();
    //connected_components_.print();
    //graph_.print();
    this->strongly_conn_.init();
    this->strongly_conn_.estimateStronglyConnectedComponents();
    // this->strongly_conn_.print();
}

void OperationsControl::buildGraph() {
    string line;
    char cLine[100];
    while (getline(cin, line)) {
        strcpy(cLine, line.c_str());
        char *n1;
        n1 = strtok(cLine, " \t\n\0");
        if (n1 == NULL) continue;
        if (n1[0] == 'S') break;
        uint32_t sourceNode = atol(n1);
        char *n2 = strtok(NULL, " \t\n\0");
        if (n2 == NULL) continue;
        uint32_t targetNode = atol(n2);
        graph_.insertEdge(sourceNode, targetNode, bidirectional_insert);
    }
}

void OperationsControl::runQueries() {
    string line;
    char cLine[100];
    // uint32_t size = 60;
    // uint32_t *batch = new uint32_t[size];
    // uint32_t counter = 0;
    while (getline(cin, line)) {
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
            if (graph_.insertEdge(sourceNode, targetNode, bidirectional_insert)) {
                //connected_components_.insertNewEdge(sourceNode, targetNode);
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
            char *node = strtok(NULL, " \t\n\0");
            if (node == NULL) continue;
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \t\n\0");
            if (node == NULL) continue;
            uint32_t targetNode = atol(node);
            cout << path_.shortestPath(sourceNode, targetNode) << endl;
            path_.reset();
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
        }
        // } else if (!strcmp(op, "F")) {
            // for (uint32_t i = 0; i < counter; i += 3) {
            //     if (batch[i] == 0) {
            //         graph_.insertEdge(batch[i + 1], batch[i + 2]);
            //     } else {
            //         cout << path_.shortestPath(batch[i + 1], batch[i + 2]) << endl;
            //         path_.reset();
            //     }
            // }
            // counter = 0;
        //connected_components_.print();
    }
    // delete[] batch;
}
