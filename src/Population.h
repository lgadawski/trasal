#ifndef POPULATION_H_
#define POPULATION_H_

#include "Individual.h"

class Population {
private:
	std::set<Individual> individuals;
	Map map;
	int populationSize;
public:
	Population(Map amap, int apopSize);

	void RandomlyCrossover(int crossoverPropability);
	void RandomlyMutate(int mutatePropability);

	Individual GetBestIndividual();

	int GetPopulationSize() {
		return populationSize;
	}
};



#endif /* POPULATION_H_ */
