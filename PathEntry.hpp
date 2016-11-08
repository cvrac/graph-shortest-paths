#ifndef GRAPHSHORTESTPATHS_PATHENTRY_H
#define GRAPHSHORTESTPATHS_PATHENTRY_H

#include <stdint.h>

struct PathEntry {
	PathEntry(uint32_t &id, uint32_t &pd, unsigned int &pathc, char &dir);
	PathEntry();
	PathEntry(const PathEntry &entr);
	PathEntry &operator=(const PathEntry &entr);
	void update(uint32_t &id, uint32_t &pd, unsigned int &pathc, char &dir);
	friend std::ostream &operator<<(std::ostream &out, const PathEntry &e);
	friend bool operator== (const PathEntry &e1, const PathEntry &e2);

	uint32_t node_id;
	uint32_t parent_id;
	unsigned int path_cost;
	char direction;
};

#endif
