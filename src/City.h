#ifndef CITY_H_
#define CITY_H_

#include <boost/dynamic_bitset.hpp>
#include <exception>

// misto reprezentuje gen jako zbiór bitów o wielkości zależnej od ilości miast
class City {
private:
	int id;
	boost::dynamic_bitset<> chromosome;


public:
	City() {}
	City(int aid, int num_bits) :
		id(aid),
		chromosome(boost::dynamic_bitset<>(num_bits, id)) {}

	int getId() const {return id;}

	std::string getChromosome() const {
		std::string buffer;
		boost::to_string(chromosome, buffer);

		return buffer;
	}
	friend bool operator< (const City &left, const City &right) { return left.id < right.id; }
};

#endif /* CITY_H_ */
