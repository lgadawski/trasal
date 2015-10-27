#ifndef CITY_H_
#define CITY_H_

#include <boost/dynamic_bitset.hpp>
#include <exception>

// misto reprezentuje gen jako zbiór bitów o wielkości zależnej od ilości miast
class City {
private:
	int id;

	boost::dynamic_bitset<> gen;

public:
	City():
		id(-1) {}
	City(int aid, int num_bits) :
		id(aid),
		gen(boost::dynamic_bitset<>(num_bits, id)) {}

	int getId() const {return id;}
	int getNumOfBits() const {return gen.size();}
	std::string getGen() const {
		std::string buffer;
		boost::to_string(gen, buffer);

		return buffer;
	}
	bool getGenBit(int bitNr) const {return gen[/*gen.size()-1-*/bitNr];}

	std::string toStringBinary(){
		std::string buffer;
		boost::to_string(gen, buffer);
		return buffer;
	}

	friend bool operator< (const City &left, const City &right) { return left.id < right.id; }
};

#endif /* CITY_H_ */
