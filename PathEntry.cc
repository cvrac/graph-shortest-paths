#include <iostream>
#include "PathEntry.h"

using namespace std;

ostream& operator<<(ostream& out, const path_entry& d) {
	out << d.nodeId << endl;
	out << "neti" << endl;
	return out;
}