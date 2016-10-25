#ifndef PATHENTRY_H
#define PATHENTRY_H

#include <stdint.h>

struct path_entry {
	uint32_t nodeId;
	uint32_t parentId;
	unsigned int pathCost;
	char direction;
	friend std::ostream& operator<<(std::ostream& out, const path_entry& e);	
	path_entry(uint32_t& id, uint32_t& parentId, unsigned int& pathC, char& dir);
};

#endif