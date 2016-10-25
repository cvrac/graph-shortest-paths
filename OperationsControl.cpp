#include "OperationsControl.h"
#include <string>
#include <cstring>
#include <iostream>
#include <stdint.h>

using namespace std;

void OperationsControl::run() {
    this->buildGraph();
    this->runQueries();
    //graph.print();
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
        char *node;
        node = strtok(cLine, " \n\0");
        if (node == NULL) {
            delete[] cLine;
            continue;
        }
        if (node[0] == 'S') {
            delete[] cLine;
            break;
        }
        uint32_t sourceNode = atol(node);
        node = strtok(NULL, " \n\0");
        if (node == NULL) {
            delete[] cLine;
            continue;
        }
        uint32_t targetNode = atol(node);
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
        op = strtok(cLine, " \n\0");
        if (op == NULL) {
            delete[] cLine;
            continue;
        }
        if (!strcmp(op, "A")) {
            char *node = strtok(NULL, " \n\0");
            if (node == NULL) {
                delete[] cLine;
                continue;
            }
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \n\0");
            if (node == NULL) {
                delete[] cLine;
                continue;
            }
            uint32_t targetNode = atol(node);
            delete[] cLine;
            graph.insertEdge(sourceNode, targetNode);
        }
        else if (!strcmp(op, "Q")) {
            char *node = strtok(NULL, " \n\0");
            if (node == NULL) {
                delete[] cLine;
                continue;
            }
            uint32_t sourceNode = atol(node);
            node = strtok(NULL, " \n\0");
            if (node == NULL) {
                delete[] cLine;
                continue;
            }
            uint32_t targetNode = atol(node);
            delete[] cLine;
            cout << path.shortestPath(sourceNode, targetNode) << endl;
        }
        else {
            delete[] cLine;
        }
    }
}