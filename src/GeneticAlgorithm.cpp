#include "GeneticAlgorithm.h"
#include <chrono>

Individual GeneticAlgorithm::Perform() {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	auto initialPopulation = shared_ptr<Population>(
			new Population(map, conf.GetPopulationSize()));
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
	cout<<"Initial population initialization time: "<< duration<<" microseconds"<<endl;

	auto currentPopulation = initialPopulation->Reproduce();
	auto whole_time = 0;
	for (int i = 0; i < GENERATION_NUMBER; ++i) {
		cout << endl << "GA debug: " << i << endl;
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		currentPopulation = initialPopulation->Reproduce();

		currentPopulation->RandomlyCrossover(conf.GetPropabilityOfCrossover());
		currentPopulation->RandomlyMutate(conf.GetPropabilityOfMutation());

		initialPopulation = currentPopulation;
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
		whole_time += duration;
		cout<<i<<" 'st generation production time: "<<duration<<" microseconds"<<endl;
	}

	cout << endl << "whole loop time " << whole_time << endl;

	auto best = initialPopulation.get()->GetBestIndividual();
	cout << endl << " END: ";
	printutils::printPath(best.GetPath());
	cout << endl << "PAth LEN: " << best.GetLength() << endl;

	return initialPopulation->GetBestIndividual();
}
