#include <iostream>
#include "ListNodePos.h"

using namespace std;

ListNodePos::ListNodePos() : exists(false) {}
ListNodePos::ListNodePos(const uint32_t &pos) : pos(pos), exists(true) {}


void ListNodePos::print() const {
    if (exists) {
        cout << pos << endl;
    }
    else {
        cout << "none" << endl;
    }
}