#ifndef CITY_H_
#define CITY_H_

#include <boost/dynamic_bitset.hpp>
#include <exception>
#include <iostream>

// misto reprezentuje gen jako zbiór bitów o wielkości zależnej od ilości miast
class City {
private:
	int id;
public:
	City(const int idd = -1) : id(idd) {}
	City(const City & copy) : id(copy.getId()) {}

	virtual ~City() {
//		std::cout << " ~city ";
	}

	int getId() const {return id;}
	std::string ToString();
	friend bool operator< (const City &left, const City &right) { return left.id < right.id; }
	friend bool operator== (const City &left, const City &right) {return left.id == right.id; }
	friend std::ostream & operator<< (std::ostream &os, const City &c){ return os<<c.getId(); }
};

#endif /* CITY_H_ */
