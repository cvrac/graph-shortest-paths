#include <iostream>
#include <stdint.h>
#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "OperationsControl.hpp"

using namespace std;

int main(int argc, char **argv) {
    uint32_t hashSize = 171;
    if (argc > 1)
        hashSize = (uint32_t ) atol(argv[1]);

    OperationsControl operationsControl(hashSize);
    operationsControl.run(hashSize);

    return 0;
}
