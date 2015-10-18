#ifndef CITY_H_
#define CITY_H_

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

#endif /* CITY_H_ */
