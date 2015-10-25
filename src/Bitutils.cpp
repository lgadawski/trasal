#include "Bitutils.h"
#include <random>
#include <exception>
#include <memory>

using namespace std;

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

int bitutils::GetNumberOfBitsNeedToRepresentValue(int val) {
	int count = 0;
	while (val > 0) {
		count++;
		val = val >> 1;
	}

	return count;
}

int randomutils::RandBetween(int min, int max) {
	std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

	return uni(rng);
}
