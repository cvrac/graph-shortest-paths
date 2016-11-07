#include <string>
#include <cstring>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iomanip>
#include "OperationsControl.h"

using namespace std;

OperationsControl::OperationsControl(uint32_t &hashSize) : path(graph, hashSize) {
    // path = new ShortestPath(graph, hashSize);
}

OperationsControl::~OperationsControl() {
    // delete path;
}

void OperationsControl::run(const uint32_t &hashSize) {
    clock_t start = clock();
    this->buildGraph();
    clock_t end = clock();
    cout << "took " << (static_cast<double>(end - start) /CLOCKS_PER_SEC) << " secs" << endl;
    sleep(1);
    this->runQueries();
}

void OperationsControl::buildGraph() {
    string line;
    char cLine[100];
    while (getline(cin, line)) {
        //char *cLine;
        //try {
        //    cLine = new char[line.length()+1];
        //}
        //catch (bad_alloc& ba) {
        //    cout << "bad_alloc caught: " << ba.what() << endl;
        //    return;
        //}
        strcpy(cLine, line.c_str());
        char *n1;
        n1 = strtok(cLine, " \t\n\0");
        if (n1 == NULL) {
            //delete[] cLine;
            continue;
        }
        if (n1[0] == 'S') {
            //delete[] cLine;
            break;
        }
        uint32_t sourceNode = atol(n1);
        char *n2 = strtok(NULL, " \t\n\0");
        if (n2 == NULL) {
            //delete[] cLine;
            continue;
        }
        uint32_t targetNode = atol(n2);
        //delete[] cLine;
        graph.insertEdge(sourceNode, targetNode);
    }
}

void OperationsControl::runQueries() {
    string line;
    char cLine[100];
    while (getline(cin, line)) {
        //char *cLine;
        //try {
        //    cLine = new char[line.length()+1];
        //}
        //catch (bad_alloc& ba) {
        //    cout << "bad_alloc caught: " << ba.what() << endl;
        //    return;
        //}
        strcpy(cLine, line.c_str());
        char *op;
        op = strtok(cLine, " \t\n\0");
        if (op == NULL) {
            //delete[] cLine;
            continue;
        }
        if (!strcmp(op, "A")) {
            char *node = strtok(NULL, " \t\n\0");
            if (node == NULL) {
                //delete[] cLine;
                continue;
            }
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \t\n\0");
            if (node == NULL) {
                //delete[] cLine;
                continue;
            }
            uint32_t targetNode = atol(node);
            //delete[] cLine;
            graph.insertEdge(sourceNode, targetNode);
        }
        else if (!strcmp(op, "Q")) {
            char *node = strtok(NULL, " \t\n\0");
            if (node == NULL) {
                //delete[] cLine;
                continue;
            }
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \t\n\0");
            if (node == NULL) {
                //delete[] cLine;
                continue;
            }
            uint32_t targetNode = atol(node);
            //delete[] cLine;
            // clock_t start = clock();
            cout << path.shortestPath(sourceNode, targetNode) << endl;
            // clock_t end = clock();
            path.reset();
            // cout << "path find took ";
            // cout.precision(5);
            // cout << setprecision(15) << fixed << ((end - start) / static_cast<double>(CLOCKS_PER_SEC)) << " secs" << endl;
        }
        else {
            //delete[] cLine;
        }
    }
}
