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
	list<City> path;
public:
	Individual(vector<int>& mapa);
	Individual& Crossover(Individual&);
	Individual& Mutate();

	long GetLength();
	list<City>& GetPath() { return path; }
};


#endif /* INDIVIDUAL_H_ */
