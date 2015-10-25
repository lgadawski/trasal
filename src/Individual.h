#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <list>
#include <iterator>
#include <boost/dynamic_bitset.hpp>
#include <boost/optional.hpp>
#include "City.h"
#include "Map.h"

using namespace std;

// osobnik, lista miast jako jeden stan
class Individual {
private:
	std::list<City> path;
	mutable int length = -1;
	boost::dynamic_bitset<> binary_repr;
	std::shared_ptr<Map> map;

public:
	Individual() {} // for testing purposes
	Individual(boost::dynamic_bitset<> chromosome, const std::shared_ptr<Map> amap) :
		binary_repr(chromosome),
		map(amap) {}
	Individual(const shared_ptr<Map> spm);// TODO po

	Individual& Crossover(const Individual&); // TODO po

	boost::optional<std::shared_ptr<Individual>> RandomlyMutate(const double mutatePropability) const;

	static bool IsCorrectIndividual(const std::shared_ptr<Individual>);

	long int GetLength() const;

	std::list<City> GetPath() const { return path; }

	boost::dynamic_bitset<> GetBinaryReprezentation() const { return binary_repr; }

	// for testing purposes
	void SetBinaryRepr(std::string);

	friend bool operator< (const Individual &left, const Individual &right) {
		return left.GetLength() < right.GetLength();
	}
};


#endif /* INDIVIDUAL_H_ */
