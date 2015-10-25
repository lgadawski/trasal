#ifndef BITUTILS_H_
#define BITUTILS_H_

namespace bitutils {
	int GetNumberOfBitsNeedToRepresentValue(int val);
}

namespace randomutils {
	// return random integer that is greater or equals min and less or equal than max
	int RandBetween(int min, int max);
}

#endif /* BITUTILS_H_ */
