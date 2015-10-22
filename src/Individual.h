#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <list>
#include <iterator>
#include <boost/dynamic_bitset.hpp>
#include "City.h"
#include "Map.h"

class Individual {
private:
	std::list<City> path;
	Map map;
	int length = -1;

public:
//	Individual(...?) {} FIXME
	Individual& Crossover(Individual&);
	Individual& Mutate();

	int GetLength();
	std::list<City> GetPath() { return path; }
	friend bool operator< (Individual &left, Individual &right) {
		return left.GetLength() < right.GetLength();
	}
};


#endif /* INDIVIDUAL_H_ */
