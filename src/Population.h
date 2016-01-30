#ifndef POPULATION_H_
#define POPULATION_H_

#include <boost/optional.hpp>
#include "Individual.h"

class Population {
private:
	std::vector<Individual> individuals;
	std::shared_ptr<Map> map;
	int population_size;

	int GetAdaptationSumLen() const;
	int GetPropabDivision(int sum) const;

	void print_summary();
public:
	Population(const std::vector<Individual> aindividuals,
			const std::shared_ptr<Map> amap, const int apopulation_size);
	Population(const std::shared_ptr<Map> amap, const int apopSize);
	Population(int* population, int* adjMatrix, int popSize, int indivSize);
	virtual ~Population() {
		std::cout << " ~population "<<endl;;
	}

	void RandomlyCrossover(const double crossoverPropability);
	void RandomlyMutate(const double mutatePropability);

	std::shared_ptr<Population> Reproduce();
	Individual GetIndividualBySeq(int seq) const;
	Individual GetBestIndividual();

	int GetPopulationSize() const {
		return population_size;
	}
	std::vector<Individual> GetIndividualList() {
		return individuals;
	}
	long GetDifferenceBetweenBestAndWorstIndividual();
};

#endif /* POPULATION_H_ */
