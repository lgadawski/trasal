#include "Individual.h"

using namespace std;

int Individual::GetLength() {
	if (length != -1) return length;

	length = 0;
	for(list<City>::iterator it = path.begin(); it != path.end(); ++it) {
		list<City>::iterator next_it = ++it;
		if (next_it != path.end()) {
			length += map.GetDistance(*it, *next_it);
		}
	}

	return length;
}
