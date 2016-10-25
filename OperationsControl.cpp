#include "OperationsControl.h"
#include <string>
#include <cstring>
#include <iostream>
#include <stdint.h>

using namespace std;

void OperationsControl::run() {
    this->buildGraph();
    this->runQueries();
//    graph.print();
}

void OperationsControl::buildGraph() {
    string line;
    while (getline(cin, line)) {
        char *cLine;
        try {
            cLine = new char[line.length()+1];
        }
        catch (bad_alloc& ba) {
            cout << "bad_alloc caught: " << ba.what() << endl;
            return;
        }
        strcpy(cLine, line.c_str());
        char *n1;
        n1 = strtok(cLine, " \t\n\0");
        if (n1 == NULL) {
            delete[] cLine;
            continue;
        }
        if (n1[0] == 'S') {
            delete[] cLine;
            break;
        }
        uint32_t sourceNode = atol(n1);
        char *n2 = strtok(NULL, " \t\n\0");
        if (n2 == NULL) {
            delete[] cLine;
            continue;
        }
        uint32_t targetNode = atol(n2);
        delete[] cLine;
        graph.insertEdge(sourceNode, targetNode);
    }
}

void OperationsControl::runQueries() {
    string line;
    while (getline(cin, line)) {
        char *cLine;
        try {
            cLine = new char[line.length()+1];
        }
        catch (bad_alloc& ba) {
            cout << "bad_alloc caught: " << ba.what() << endl;
            return;
        }
        strcpy(cLine, line.c_str());
        char *op;
        op = strtok(cLine, " \t\n\0");
        if (op == NULL) {
            delete[] cLine;
            continue;
        }
        if (!strcmp(op, "A")) {
            char *node = strtok(NULL, " \t\n\0");
            if (node == NULL) {
                delete[] cLine;
                continue;
            }
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \t\n\0");
            if (node == NULL) {
                delete[] cLine;
                continue;
            }
            uint32_t targetNode = atol(node);
            delete[] cLine;
            graph.insertEdge(sourceNode, targetNode);
        }
        else if (!strcmp(op, "Q")) {
            char *node = strtok(NULL, " \t\n\0");
            if (node == NULL) {
                delete[] cLine;
                continue;
            }
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \t\n\0");
            if (node == NULL) {
                delete[] cLine;
                continue;
            }
            uint32_t targetNode = atol(node);
            delete[] cLine;
            path = new ShortestPath(this->graph);
            cout << path->shortestPath(sourceNode, targetNode) << endl;
            delete path;
        }
        else {
            delete[] cLine;
        }
    }
}