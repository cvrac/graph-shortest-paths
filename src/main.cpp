#include <stdint.h>

#include "OperationsControl.hpp"

using namespace std;

int main(int argc, char **argv) {
    int threads = 6;
    if (argc > 1) {
        threads = atoi(argv[1]);
    }
    OperationsControl operationsControl(threads);
    operationsControl.run();
    return 0;
}
