#ifndef GRAPHSHORTESTPATHS_LISTNODEPOS_H
#define GRAPHSHORTESTPATHS_LISTNODEPOS_H

#include <stdint.h>

class ListNodePos {

private:
    uint32_t listNodePos;
    bool exists;

public:
    ListNodePos();
    ListNodePos(const uint32_t &listNodePos);
    ~ListNodePos() {}
    bool getExists() const {return exists;}
    uint32_t getListNodePos() const {return listNodePos;}
    void setListNodePos(uint32_t listNodePos) {this->listNodePos = listNodePos;}
    void setExists(bool flag) {exists = flag;}
    void print() const;
};

#endif //GRAPHSHORTESTPATHS_LISTNODEPOS_H
