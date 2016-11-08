#include <iostream>
#include <cstring>
#include "PathEntry.hpp"

using namespace std;

PathEntry::PathEntry() : node_id(0), parent_id(0), path_cost(0), direction('-') { }

PathEntry::PathEntry(const PathEntry &entr) : node_id(entr.node_id), parent_id(entr.parent_id),
	path_cost(entr.path_cost), direction(entr.direction) { }

PathEntry& PathEntry::operator=(const PathEntry& entr) {
	if (entr == *this)
		return *this;
	memcpy(this, &entr, sizeof(entr));
	return *this;
}

PathEntry::PathEntry(uint32_t& id, uint32_t& pd, unsigned int& pathc, char& dir) :
	node_id(id), parent_id(pd), path_cost(pathc), direction(dir) { }


ostream& operator<<(ostream& out, const PathEntry& d) {
	out << d.node_id << " " << d.parent_id << " " << d.path_cost << " "
	<< d.direction << endl;;
	return out;
}

bool operator== (const PathEntry& e1, const PathEntry& e2) {
	if (e1.node_id == e2.node_id && e1.parent_id == e2.parent_id && e1.path_cost == e2.path_cost && e1.direction == e2.direction)
		return true;
	else
		return false;
}

void PathEntry::update(uint32_t& id, uint32_t &pd, unsigned int &pathc, char &dir) {
	this->node_id = id;
	this->parent_id = pd;
	this->path_cost = pathc;
	this->direction = dir;
}
