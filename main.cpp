#include <iostream>
#include <stdint.h>
#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "OperationsControl.hpp"

using namespace std;

int main(int argc, char **argv) {
    uint32_t hashSize = 131;
    char mode = 'n';
    float cc_threshold = 1;
    if (argc > 1) {
        mode = argv[1][0];
    }
    if (argc > 2) {
        cc_threshold = atof(argv[2]);
    }

    OperationsControl operationsControl(cc_threshold);
    operationsControl.run(mode);

    return 0;
}
