#include "GeneticAlgorithm.h"

Individual GeneticAlgorithm::Perform() {
	Population initialPopulation(map, conf.GetPopulationSize());

	Population currentPopulation = Reproduce(initialPopulation);;
	for (int i = 0; i < GENERATION_NUMBER; ++i) {
		currentPopulation = Reproduce(initialPopulation);

		currentPopulation.RandomlyCrossover(conf.GetPropabilityOfCrossover());
		currentPopulation.RandomlyMutate(conf.GetPropabilityOfMutation());

		// eval currentPopulation TODO lg
		initialPopulation = currentPopulation;
	}
	// TODO
	return initialPopulation.GetBestIndividual();
}

Population& GeneticAlgorithm::Reproduce(Population &population) {
	// TODO lg
//	return descendant;
}
