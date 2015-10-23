#ifndef CITY_H_
#define CITY_H_

#include <boost/dynamic_bitset.hpp>


// misto reprezentuje gen jako zbiór bitów o wielkości zależnej od ilości miast
class City {
private:
	int id;
	int num_of_bits;
	boost::dynamic_bitset<> gen;
public:
	City(){};
	City(int aid, int num_bits) :
		id(aid),
		num_of_bits(num_bits),
		gen(boost::dynamic_bitset<>(num_bits, id)){};

	int getId()const{return id;};
	int getNumberOfBits(){return num_of_bits;}

	friend bool operator< (const City &left, const City &right) { return left.id < right.id; }
};


#endif /* CITY_H_ */
