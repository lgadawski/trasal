#include "GeneticAlgorithm.h"

Individual GeneticAlgorithm::Perform() {
	Population initialPopulation(map, conf.GetPopulationSize());

	// evaluate initialPopulation FIXME
	Individual bestIndividual = initialPopulation.GetBestIndividual();

	for (int i = 0; i < GENERATION_NUMBER; ++i) {
		Population currentPopulation = Reproduce(initialPopulation);

		currentPopulation.RandomlyCrossover(conf.GetPropabilityOfCrossover());
		currentPopulation.RandomlyMutate(conf.GetPropabilityOfMutation());

		// eval currentPopulation FIXME
		initialPopulation = currentPopulation;
	}
	// FIXME
//	return bestIndividual;
}

Population& GeneticAlgorithm::Reproduce(Population &population) {
	// FIXME
//	return descendant;
}
