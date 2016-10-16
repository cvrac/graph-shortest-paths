#include <iostream>
#include "ListNodePos.h"

using namespace std;

ListNodePos::ListNodePos() : exists(false) {}
ListNodePos::ListNodePos(const uint32_t &listNodePos) : listNodePos(listNodePos), exists(true) {}


void ListNodePos::print() const {
    if (exists) {
        cout << listNodePos << endl;
    }
    else {
        cout << "none" << endl;
    }
}