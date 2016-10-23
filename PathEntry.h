#ifndef PATHENTRY_H
#define PATHENTRY_H

#include <stdint.h>

struct path_entry {
	uint32_t nodeId;
	uint32_t parentId;
	uint32_t pathCost;
	uint32_t direction;
	friend std::ostream& operator<<(std::ostream& out, const path_entry& e);	
};

#endif