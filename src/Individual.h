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

	Individual(shared_ptr<Map> spm);// TODO po

	Individual& Crossover(Individual&); // TODO po
	boost::optional<std::shared_ptr<Individual>> RandomlyMutate(const double mutatePropability) const;

	static bool IsCorrectIndividual(std::shared_ptr<Individual>);

	long int GetLength() const;
	std::list<City> GetPath() const { return path; }
	friend bool operator< (const Individual &left, const Individual &right) {
		return left.GetLength() < right.GetLength();
	}
};


#endif /* INDIVIDUAL_H_ */
