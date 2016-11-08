#ifndef GRAPHSHORTESTPATHS_LISTNODEPOS_H
#define GRAPHSHORTESTPATHS_LISTNODEPOS_H

#include <stdint.h>

#include <iostream>

struct ListNodePos {

public:
    ListNodePos() : exists(false) {}
    ListNodePos(const uint32_t &pos) : pos(pos), exists(true) {}
    ~ListNodePos() {}
    bool getExists() const {return exists;}
    uint32_t getPos() const {return pos;}
    void print() const {
        if (exists) {
            std::cout << pos << std::endl;
        }
        else {
            std::cout << "none" << std::endl;
        }
    }

    uint32_t pos;
    bool exists;
};

#endif //GRAPHSHORTESTPATHS_LISTNODEPOS_H
