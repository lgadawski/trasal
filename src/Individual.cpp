#include "Individual.h"

long Individual::GetLength() {
	long length = 0;
	for(list<City>::iterator it = path.begin(); it != path.end(); ++it) {
		list<City>::iterator next_it = ++it;
		if (next_it != path.end()) {

		}
	}
	return 0;
}
