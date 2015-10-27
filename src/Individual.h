#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <list>
#include <iterator>
#include <boost/dynamic_bitset.hpp>
#include <boost/optional.hpp>
#include "City.h"
#include "Map.h"

using namespace std;

// osobnik, lista miast jako jeden stan
class Individual {
private:
	std::list<City> path;
	mutable int length = -1;
	boost::dynamic_bitset<> binary_repr;
	std::shared_ptr<Map> map;

public:
	Individual() {} // for testing purposes
	Individual(boost::dynamic_bitset<> chromosome, const std::shared_ptr<Map> amap) :
		binary_repr(chromosome),
		map(amap) {}
	Individual(const Individual & copy) :
		binary_repr(copy.binary_repr),
		map(copy.map),
		length(copy.length)
	{
		cout<<"con - "<<bitutils::ToStringBitSet(this->binary_repr)<<endl;
		this->path = list<City>(copy.GetPath());
		for(std::list<City>::iterator it = path.begin(); it != path.end() ; it++){
					cout<<it->getId()<<endl;
		}

		std::copy(copy.path.begin(),copy.path.end(), this->path.begin());
	}
	Individual(const shared_ptr<Map> spm);// TODO po

	boost::optional<std::shared_ptr<pair<Individual,Individual>>> RandomlyCrossover(const double crossoverPprobability , Individual second); // TODO po

	boost::optional<std::shared_ptr<Individual>> RandomlyMutate(const double mutatePropability) const;

	static bool IsCorrectIndividual(const std::shared_ptr<Individual>);

	long int GetLength() const;

	std::list<City> GetPath() const { return path; }

	boost::dynamic_bitset<> GetBinaryReprezentation() const { return binary_repr; }
	bool GetBit(int bitNr) const { return binary_repr[bitNr]; }
	void SetBit(int bitNr, bool value){binary_repr[bitNr]=value;}
	// for testing purposes
	void SetBinaryRepr(std::string);
	void SetBinaryRepr(boost::dynamic_bitset<> repr);
	friend bool operator< (const Individual &left, const Individual &right) {
		return left.GetLength() < right.GetLength();
	}


	void SetPath(const std::list<City>& path){this->path = path;}
	void SetPath(boost::dynamic_bitset<> binary, int numOfBitsPerCity);
};


#endif /* INDIVIDUAL_H_ */
