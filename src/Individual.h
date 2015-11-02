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
	std::vector<City> path;
	std::shared_ptr<Map> map;
	mutable int length = -1;

	bool ContainsCity(City c);

public:
	Individual() {}
	Individual(const std::shared_ptr<Map> amap);
	Individual(const Individual & copy) :
		map(copy.map),
		length(copy.length)
	{
		this->path = copy.GetPath();
	}

	~Individual() { std::cout << " ~individual "; }

	void swap_path(int first_idx, int sec_idx) { std::swap(path[first_idx], path[sec_idx]); }

	boost::optional<pair<Individual,Individual>> RandomlyCrossover(const double crossoverPprobability , Individual second);

	boost::optional<std::shared_ptr<Individual>> RandomlyMutate(const double mutatePropability) const;

	static bool IsCorrectIndividual(const std::shared_ptr<Individual>);

	long int GetLength() const;

	std::vector<City> GetPath() const { return path; }

	// for testing purposes
	friend bool operator< (const Individual &left, const Individual &right) {
		// FIXME Segmentation Fault
		return true;
//		return left.GetLength() < right.GetLength();
	}

	friend ostream & operator<< (ostream &os, const Individual &ind){
		cout << ind.path.size() << endl;
		int size = ind.path.size()-1;
		for(int i = 0 ; i < size ; i++){
			os<<ind.path[i]<<"->";
		}
		if(!ind.path.empty())
			os<<ind.path.back();
		return os;
	}

	friend bool operator== (const Individual &left, const Individual &right) {
		return left.GetPath() == right.GetPath();
	}

	void SetPath(const std::vector<City>& path){this->path = path;}
	void SetCity(int position, City c){path[position] = c;};
	City GetCity(int position){return path[position];};
	void resetPath();
};


#endif /* INDIVIDUAL_H_ */
