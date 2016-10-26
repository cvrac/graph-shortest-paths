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

bool operator== (const path_entry& e1, const path_entry& e2) {
	if (e1.nodeId == e2.nodeId && e1.parentId == e2.parentId && e1.pathCost == e2.pathCost && e1.direction == e2.direction)
		return true;
	else
		return false;
}