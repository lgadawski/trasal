#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <list>
#include <boost/dynamic_bitset.hpp>

using namespace std;

// misto reprezentuje gen jako zbiór bitów o wielkości zależnej od ilości miast
class City {
private:
	int id;
	boost::dynamic_bitset<> gen;
public:
	City(int aid, int num_bits) :
		id(aid),
		gen(boost::dynamic_bitset<>(num_bits, id)) {}

	friend bool operator< (const City &left, const City &right) { return left.id < right.id; }
};

// osobnik, lista miast jako jeden stan
class Individual {
private:
	list<City> path;
public:
	Individual& Crossover(Individual&);
	Individual& Mutate();

	const list<City>& GetPath() { return path; }
};


#endif /* INDIVIDUAL_H_ */
