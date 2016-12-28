#!/bin/bash

for ((n=0;n<10;n++)); do ./gsp s < datasets/tiny/tinyGraph.txt < datasets/tiny/tinyStatic_FINAL.txt; done
