#ifndef UTILS_H_
#define UTILS_H_
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include "City.h"

namespace bitutils {
	int GetNumberOfBitsNeedToRepresentValue(int val);
	std::string ToStringBitSet(boost::dynamic_bitset<> bit_set);
}

namespace randomutils {
	// return random integer that is greater or equals min and less or equal than max
	int RandBetween(int min, int max);
}

namespace printutils{
	void printPath(std::vector<City> & path);
}
#endif /* UTILS_H_ */
