#include "OperationsControl.hpp"

#include <string>
#include <iostream>

#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

using namespace std;

OperationsControl::OperationsControl(const uint32_t pool_size) :
        paths_(pool_size),  strongly_conn_(graph_),
        cc_(graph_), grail_index_(graph_, strongly_conn_),
        res_array_(40), scheduler_(pool_size, res_array_), mode_('c') {

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

void OperationsControl::run() {
    clock_t start = clock();
    this->buildGraph();
    cout << "buildGraph: " << (clock() - start) / (double) CLOCKS_PER_SEC << "\n\n";

    char ch;
    while ((ch = getchar()) == '\n');
    if (ch == 'S') {
        mode_ = 's';
    }
    while ((ch = getchar()) != '\n');

    if (mode_ == 'c') {
        cc_.estimateConnectedComponents();
    }
    if (mode_ == 's') {
        // start = clock();
        this->strongly_conn_.init();
        this->strongly_conn_.estimateStronglyConnectedComponents();
//        cout << "SCC: " << (clock() - start) / (double) CLOCKS_PER_SEC << "\n";
        //this->strongly_conn_.print();
        // start = clock();
        this->grail_index_.buildGrailIndex();
//        cout << "Hypergraph and grail build: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
    }

    for (uint32_t i = 0; i < paths_.getElements(); i++)
        paths_[i]->init();
    //start = clock();
    this->runQueries();
    //cout << "runQueries: " << (clock() - start) / (double) CLOCKS_PER_SEC << endl;
    // cout << "Total swaps: " << graph_.Graph::swaps_ << endl;
}

void OperationsControl::parseNodeIds(uint32_t *source, uint32_t *target) {
    uint32_t sourceNode = *source;
    uint32_t ch;
    while (ch != ' ' && ch != '\t') {
        if (ch >= '0' && ch <= '9') {
            sourceNode = sourceNode * 10 + (ch - '0');
        }
        ch = getchar();
    }
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

void OperationsControl::buildGraph() {
    int ch;
    uint32_t sourceNode, targetNode;
    while ((ch = getchar()) != EOF && ch != 'S') {
        sourceNode = ch - '0';
        parseNodeIds(&sourceNode, &targetNode);
        graph_.insertEdge(sourceNode, targetNode, 'N', 0);
    }
}

void OperationsControl::runQueries() {
    Job *new_job;
    uint32_t sourceNode, targetNode;
    int ch;
    uint32_t queries_count = 0;
    uint32_t current_version = 0;
    bool version_change = false;

    while ((ch = getchar()) != EOF) {

        if (ch == 'F') {
            /* Not needed unless CC::insertNewEdge assertion fails. (there are no new nodes in the workload files) */
            /*if (mode != 's') {
                for (uint32_t i = 0 ; i < paths_.getElements() ; i++) {
                    paths_[i]->increaseExploreSet();
                }
            }*/
            if (res_array_.getSize() < queries_count) {
                res_array_.increaseSize(queries_count);
            }
            res_array_.setElements(queries_count);
            scheduler_.executeAllJobs();

            for (uint32_t i = 0; i < res_array_.getElements(); i++) {
                cout << res_array_[i] << "\n";
            }
            queries_count = 0;
            if (mode_ == 'c') {
                if (cc_.needRebuilding()) {
                    cc_.rebuildIndexes();
                }
                cc_.setQueriesCount(0);
                cc_.setUpdateIndexUseCount(0);
            }
        } else if (ch == 'Q') {
            ch = getchar();
            ch = getchar();
            sourceNode = ch - '0';
            parseNodeIds(&sourceNode, &targetNode);

            uint32_t total_nodes = graph_.getNodes('N');
            if (sourceNode >= total_nodes || targetNode >= total_nodes) {
                if (res_array_.getSize() < queries_count) {
                    res_array_.increaseSize(queries_count);
                }
                res_array_[queries_count++] = -1;
                continue;
            }

            if (mode_ != 's') {
                if (! version_change) {
                    version_change = true;
                }
                new_job = new DynamicJob(queries_count, sourceNode, targetNode, current_version, paths_, cc_, mode_);
            } else {
                new_job = new StaticJob(queries_count, sourceNode, targetNode, paths_, strongly_conn_, grail_index_);
            }
            scheduler_.submitJob(new_job);
            ++queries_count;

        } else if (ch == 'A') {
            if (version_change) {
                current_version++;
                version_change = false;
            }
            ch = getchar();
            ch = getchar();
            sourceNode = ch - '0';
            parseNodeIds(&sourceNode, &targetNode);

            if (graph_.insertEdge(sourceNode, targetNode, 'N', current_version) && mode_ == 'c') {
                cc_.insertNewEdge(sourceNode, targetNode, current_version);
            }
        }
    }
    scheduler_.terminateThreads();
}
