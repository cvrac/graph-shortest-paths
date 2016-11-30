#include <iostream>
#include <stdint.h>
#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "OperationsControl.hpp"

using namespace std;

int main(int argc, char **argv) {
    uint32_t hashSize = 131;
    char mode = 'n';
    float cc_threshold = 0.49;
    if (argc > 1) {
        hashSize = (uint32_t) atol(argv[1]);
    }
    if (argc > 2) {
        mode = argv[2][0];
    }
    if (argc > 3) {
        cc_threshold = atof(argv[3]);
    }

    OperationsControl operationsControl(hashSize, cc_threshold);
    operationsControl.run(hashSize, mode);

    return 0;
}
