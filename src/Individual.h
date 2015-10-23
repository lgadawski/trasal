#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <list>
#include <iterator>
#include <boost/dynamic_bitset.hpp>
#include "City.h"
#include "Map.h"



using namespace std;

// osobnik, lista miast jako jeden stan
class Individual {
private:
	std::list<City> path;
	int length = -1;
	boost::dynamic_bitset<> binary_repr;
	Map map;
public:

	Individual(shared_ptr<Map> spm);

	Individual& Crossover(Individual&);
	Individual& Mutate();

	long int GetLength();
	std::list<City> GetPath() { return path; }
	friend bool operator< (Individual &left, Individual &right) {
		return left.GetLength() < right.GetLength();
	}
};


#endif /* INDIVIDUAL_H_ */
