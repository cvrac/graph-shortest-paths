#include <iostream>
#include <cstring>
#include "PathEntry.h"

using namespace std;

path_entry::path_entry() : nodeId(0), parentId(0), pathCost(0), direction('-') { }

path_entry::path_entry(const path_entry &entr) : nodeId(entr.nodeId), parentId(entr.parentId), pathCost(entr.pathCost), direction(entr.direction) {
	cout << "created man" << endl;
}

path_entry& path_entry::operator=(const path_entry& entr) {
	if (entr == *this)
		return *this;
	memcpy(this, &entr, sizeof(entr));
	return *this;
}

path_entry::path_entry(uint32_t& id, uint32_t& pd, unsigned int& pathC, char& dir) :
	nodeId(id), parentId(pd), pathCost(pathC), direction(dir) {}


ostream& operator<<(ostream& out, const path_entry& d) {
	out << d.nodeId << " " << d.parentId << " " << d.pathCost << " " << d.direction << endl;;
	// out << "neti" << endl;
	return out;
}

bool operator== (const path_entry& e1, const path_entry& e2) {
	if (e1.nodeId == e2.nodeId && e1.parentId == e2.parentId && e1.pathCost == e2.pathCost && e1.direction == e2.direction)
		return true;
	else
		return false;
}

void path_entry::update(uint32_t& id, uint32_t &pd, unsigned int &pathC, char &dir) {
	this->nodeId = id;
	this->parentId = pd;
	this->pathCost = pathC;
	this->direction = dir;
}
