#include "GeneticAlgorithm.h"

Individual GeneticAlgorithm::Perform() {
	auto initialPopulation = shared_ptr<Population>(
			new Population(map, conf.GetPopulationSize()));

	auto currentPopulation = initialPopulation->Reproduce();
	for (int i = 0; i < GENERATION_NUMBER; ++i) {
		cout << endl << "GA debug: " << i << endl;
		currentPopulation = initialPopulation->Reproduce();

		currentPopulation->RandomlyCrossover(conf.GetPropabilityOfCrossover());
		currentPopulation->RandomlyMutate(conf.GetPropabilityOfMutation());

		// eval currentPopulation TODO lg
		initialPopulation = currentPopulation;
	}
	// TODO
	cout << endl << " END: ";
	printutils::printPath(
			initialPopulation.get()->GetBestIndividual().GetPath());

	return initialPopulation->GetBestIndividual();
}
