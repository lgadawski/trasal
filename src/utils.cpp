#include "City.h"
#include <iostream>
#include <random>
#include <exception>
#include <memory>
#include <vector>
#include "utils.h"

using namespace std;

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)

int bitutils::GetNumberOfBitsNeedToRepresentValue(int val) {
	int count = 0;
	while (val > 0) { //
		count++;
		val = val >> 1;
	}

	return count;
}

std::string bitutils::ToStringBitSet(boost::dynamic_bitset<> bit_set) {
	string result;
	for (uint i = 0; i < bit_set.size(); i++) {
		if (bit_set[i]) {
			result.append("1");
		} else {
			result.append("0");
		}
	}
	return result;
}

int randomutils::RandBetween(int min, int max) {
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	return uni(rng);
}

void printutils::printPath(const std::vector<City> &path) {
	int size = path.size();
	for (int i = 0; i < size - 1; ++i) {
		std::cout << path[i] << "->";
	}
	if (!path.empty()) {
		cout << path.back() << endl;
	}
}

