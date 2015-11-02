#ifndef POPULATION_H_
#define POPULATION_H_

#include <boost/optional.hpp>
#include "Individual.h"

class Population {
private:
	std::set<Individual> individuals;
	std::set<Individual> mutatedIndividuals;
	std::shared_ptr<Map> map;
	int populationSize;

public:
	Population(const std::shared_ptr<Map> amap, const int apopSize);

	~Population() { std::cout << " ~population"; }

	void RandomlyCrossover(const double crossoverPropability);
	void RandomlyMutate(const double mutatePropability);

	Individual GetBestIndividual();

	int GetPopulationSize() const { return populationSize; }
};



#endif /* POPULATION_H_ */
