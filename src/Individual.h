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
	std::shared_ptr<Map> map;
	std::vector<City> path;
	mutable int length = -1;

	int seq;
	double propability;
	double cum_dist;

	bool ContainsCity(City c);

public:
	Individual() {}
	Individual(const std::shared_ptr<Map> amap);
	Individual(const Individual & copy) :
		map(copy.map),
		length(copy.length),
		seq(copy.seq),
		propability(copy.propability),
		cum_dist(copy.cum_dist)
	{
		this->path = copy.GetPath();
	}

	virtual ~Individual() {
//		std::cout << " ~individual ";
	}

	void swap_path(int first_idx, int sec_idx) { std::swap(path[first_idx], path[sec_idx]); }

	boost::optional<pair<Individual,Individual>> RandomlyCrossover(const double crossoverPprobability , Individual second);

	boost::optional<std::shared_ptr<Individual>> RandomlyMutate(const double mutatePropability) const;

	static bool IsCorrectIndividual(const std::shared_ptr<Individual>);

	long int GetLength() const;

	long int GetAdaptationValue() const {
		// FIXME correct to: (1 - #GetLength()), to promote smaller results
		return GetLength();
	}

	void SetCumulativeDistribution(double acum_distr) { cum_dist = acum_distr; }
	double GetPropability() const { return propability; }
	void SetSeq(int aseq) { seq = aseq; }
	int GetSeq() const { return seq; }
	std::vector<City> GetPath() const { return path; }

	//	propab = (len_sum - x) / (sum(len_sum - x_i))
	void CalculatePropability(int sum, int sum_division) {
		double d_sum = (double) sum, d_sum_divisiont = (double) sum_division, d_len = (double) GetLength();

		propability = (d_sum - d_len) /d_sum_divisiont;
	}

	friend bool operator< (const Individual &left, const Individual &right) { return left.GetLength() < right.GetLength(); }
	friend bool operator== (const Individual &left, const Individual &right) { return left.GetPath() == right.GetPath(); }

	friend ostream & operator<< (ostream &os, const Individual &ind){
		cout << "Individual size: " << ind.path.size() << ", path: ";
		int size = ind.path.size()-1;
		for(int i = 0 ; i < size ; i++){
			os<<ind.path[i]<<"->";
		}
		if(!ind.path.empty())
			os<<ind.path.back();
		return os;
	}

	void SetPath(const std::vector<City>& path){this->path = path;}
	void SetCity(int position, City c){path[position] = c;};
	City GetCity(int position){return path[position];};
	void resetPath();
};


#endif /* INDIVIDUAL_H_ */
