#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include <exception>
#include "Map.h"
#include "Configuration.h"
#include "Individual.h"
#include "Population.h"

class GeneticAlgorithm {
private:
	Map map;
	Configuration conf;

	GeneticAlgorithm() { throw std::exception(); }

	// number of generations, STOP condition for algorithm
	const int GENERATION_NUMBER = 100;

public:
	GeneticAlgorithm(Map& amap, Configuration& aconf) :
		map(amap),
		conf(aconf) {}

	Individual Perform();
	Population& Reproduce(Population &population);
	Map GetMap() { return map; }
	Configuration GetConfiguration() { return conf; }
};



#endif /* GENETICALGORITHM_H_ */
