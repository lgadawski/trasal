#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <list>
#include <iterator>
#include <boost/dynamic_bitset.hpp>
#include "Map.h"
#include "City.h"


using namespace std;

// osobnik, lista miast jako jeden stan
class Individual {
private:

	list<City> city_path;
	boost::dynamic_bitset<> binary_repr;
public:

	Individual(shared_ptr<Map> spm);

	Individual& Crossover(Individual&);
	Individual& Mutate();

	long GetLength();
	list<City>& GetPath() { return city_path; }
};


#endif /* INDIVIDUAL_H_ */
