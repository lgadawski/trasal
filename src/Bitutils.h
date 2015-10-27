#ifndef BITUTILS_H_
#define BITUTILS_H_
#include <boost/dynamic_bitset.hpp>
namespace bitutils {
	int GetNumberOfBitsNeedToRepresentValue(int val);
	std::string ToStringBitSet(boost::dynamic_bitset<> bit_set);
}

namespace randomutils {
	// return random integer that is greater or equals min and less or equal than max
	int RandBetween(int min, int max);
}

#endif /* BITUTILS_H_ */
