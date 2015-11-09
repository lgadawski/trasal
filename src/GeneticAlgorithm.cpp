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

		initialPopulation = currentPopulation;
	}

	auto best = initialPopulation.get()->GetBestIndividual();
	cout << endl << " END: ";
	printutils::printPath(best.GetPath());
	cout << endl << "PAth LEN: " << best.GetLength() << endl;

	return initialPopulation->GetBestIndividual();
}
