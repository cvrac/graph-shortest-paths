#ifndef GRAPHSHORTESTPATHS_LISTNODEPOS_H
#define GRAPHSHORTESTPATHS_LISTNODEPOS_H

#include <stdint.h>

class ListNodePos {

private:
    uint32_t pos;
    bool exists;

public:
    ListNodePos();
    ListNodePos(const uint32_t &pos);
    ~ListNodePos() {}
    bool getExists() const {return exists;}
    uint32_t getPos() const {return pos;}
    void print() const;
};

#endif //GRAPHSHORTESTPATHS_LISTNODEPOS_H
