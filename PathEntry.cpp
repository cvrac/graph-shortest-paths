#include <iostream>
#include "PathEntry.h"

using namespace std;

path_entry::path_entry(uint32_t& id, uint32_t& parentId, unsigned int& pathC, char& dir) :
	nodeId(id), parentId(id), pathCost(pathC), direction(dir) {}


ostream& operator<<(ostream& out, const path_entry& d) {
	out << d.nodeId << endl;
	out << "neti" << endl;
	return out;
}