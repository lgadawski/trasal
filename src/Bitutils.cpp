#include "Bitutils.h"

int bitutils::GetNumberOfBitsNeedToRepresentValue(int val) {
	int count = 0;
	while (val > 0) {
		count++;
		val = val >> 1;
	}

	return count;
}
