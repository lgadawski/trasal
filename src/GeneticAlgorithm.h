#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include <exception>
#include "Map.h"
#include "Configuration.h"
#include "Individual.h"
#include "Population.h"

class GeneticAlgorithm {
private:
	std::shared_ptr<Map> map;
	Configuration conf;

	GeneticAlgorithm() {
		throw std::runtime_error("GA empty constructor");
	}

	// number of generations, STOP condition for algorithm
	const int GENERATION_NUMBER = 3;

	Population& Reproduce(Population &population);
public:
	GeneticAlgorithm(shared_ptr<Map> amap, Configuration& aconf) :
			map(amap), conf(aconf) {
	}

	Individual Perform();
	shared_ptr<Map> GetMap() {
		return map;
	}
	Configuration GetConfiguration() {
		return conf;
	}
};

#endif /* GENETICALGORITHM_H_ */
