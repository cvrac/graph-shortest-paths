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
OperationsControl::OperationsControl(const float &cc_threshold, const uint32_t pool_size) :
 paths_(pool_size),  strongly_conn_(graph_),
 connected_components_(graph_, cc_threshold), grail_index_(graph_, strongly_conn_),
 res_array_(40), scheduler_(pool_size, res_array_) {


    for (uint32_t i = 0; i < pool_size; i++) {
        paths_[i] = new ShortestPath(graph_, strongly_conn_, grail_index_);
    }
    paths_.setElements(pool_size);
}

OperationsControl::~OperationsControl() {
    for (uint32_t i = 0; i < paths_.getElements(); i++) {
        delete paths_[i];
        paths_[i] = NULL;
    }
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
        // start = clock();
        this->strongly_conn_.init();
        this->strongly_conn_.estimateStronglyConnectedComponents();
//        cout << "SCC: " << (clock() - start) / (double) CLOCKS_PER_SEC << "\n";
        //this->strongly_conn_.print();
        // start = clock();
        this->grail_index_.buildGrailIndex();

//        cout << "Hypergraph and grail build: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
        //graph_.print();
    }

    for (uint32_t i = 0; i < paths_.getElements(); i++)
        paths_[i]->init();
    //start = clock();
    this->runQueries(mode);
    //cout << "runQueries: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
    // cout << "Total swaps: " << graph_.Graph::swaps_ << endl;
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
    bool bidirectional_insert = (mode == 'c');
    Job *new_job;
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
    uint32_t counter = 0;

    while ((ch = getchar()) == '\n') continue;
    while ((ch = getchar()) != '\n') continue;

    while ((ch = getchar()) != EOF) {

        if (ch == 'F') {
            // cout << res_array_.getElements() << endl;
            if (res_array_.getSize() < counter) {
                // cout << "yes" << endl;
                res_array_.increaseSize(counter);
            }

            res_array_.setElements(counter);
            scheduler_.executeAllJobs();
            // break;
            // cout << "results = " << res_array_.getElements() << endl;
            for (uint32_t i = 0; i < res_array_.getElements(); i++) {
                cout << res_array_[i] << "\n";
            }
            counter = 0;
        } else if (ch == 'Q') {
            ch = getchar();
            ch = getchar();
            sourceNode = ch - '0';
            parseNodeIds(&sourceNode, &targetNode);

            uint32_t total_nodes = graph_.getNodes('N');
            if (sourceNode >= total_nodes || targetNode >= total_nodes) {
                if (res_array_.getSize() < counter) {
                    // cout << "yes" << endl;
                    res_array_.increaseSize(counter);
                }
                res_array_[counter++] = -1;
                continue;
            }

            if (mode == 'n') {
                new_job = new DynamicJob(counter, sourceNode, targetNode, paths_, connected_components_);
            } else if (mode == 's') {
                new_job = new StaticJob(counter, sourceNode, targetNode, paths_, strongly_conn_, grail_index_);
            }
            scheduler_.submitJob(new_job);
            ++counter;

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
    scheduler_.terminateThreads();
//    cout << "Search skips: " << search_skips << endl;
}
