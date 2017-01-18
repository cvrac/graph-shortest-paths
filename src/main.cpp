#include <stdint.h>

#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "OperationsControl.hpp"

using namespace std;

int main(int argc, char **argv) {
    char mode = 'n';
    float cc_threshold = 1;
    if (argc > 1) {
        mode = argv[1][0];
    }
    if (argc > 2) {
        cc_threshold = atof(argv[2]);
    }

    OperationsControl operationsControl(cc_threshold, 2);
    operationsControl.run(mode);

    return 0;
}
