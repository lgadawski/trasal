#include "GeneticAlgorithm.h"
#include <chrono>

Individual GeneticAlgorithm::Perform() {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
//	auto initialPopulation = shared_ptr<Population>(new Population(map, conf.GetPopulationSize()));
	int* initialPopulation = createPopulationFromMap(this->map.get(), conf.GetPopulationSize(), this->map->getMapSize());
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
//	cout<<"Initial population initialization time: "<< duration<<" microseconds"<<endl;

	//start broadcast
	int popSize=-1;
	int indSize=-1;
	int* smallPulationInt=NULL;
	int* adjMatrix=NULL;
	//end broadcast

//	auto currentPopulation = initialPopulation->Reproduce();
	shared_ptr<Population> initialPopulationSP(new Population(smallPulationInt, adjMatrix, popSize, indSize));
	auto currentPopulation = initialPopulationSP->Reproduce();
	auto whole_time = 0;
	for (int i = 0; i < GENERATION_NUMBER; ++i) {
//		cout << endl << "GA debug: " << i << endl;
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
//		auto absBestWorst = initialPopulation->
		currentPopulation = initialPopulationSP->Reproduce();

		currentPopulation->RandomlyCrossover(conf.GetPropabilityOfCrossover());
		currentPopulation->RandomlyMutate(conf.GetPropabilityOfMutation());

		initialPopulation = currentPopulation;
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
		whole_time += duration;

//		cout<<i<<" 'st generation production time: "<<duration<<" microseconds"<<endl;
	}

	cout << endl << "whole loop time " << whole_time << endl;

	auto best = initialPopulationSP.get()->GetBestIndividual();
//	cout << endl << " END: ";
//	printutils::printPath(best.GetPath());
//	cout << endl << "PAth LEN: " << best.GetLength() << endl;

	return initialPopulationSP->GetBestIndividual();
}

int* GeneticAlgorithm::createPopulationFromMap(Map* mapa, int populationSize, int individualSize){
	int * population = new int[populationSize*individualSize];
	Population p=Population(shared_ptr<Map>(mapa), populationSize);

	int oneDpos = 0;
	for(int i = 0; i<p.GetIndividualList().size(); i++){
		Individual individual = p.GetIndividualBySeq(i);
		for(int j = 0; j<individual.GetPath().size(); j++){
			population[oneDpos] = individual.GetCity(i);
			oneDpos++;
		}
	}

	return population;
}

shared_ptr<Population> GeneticAlgorithm::createPopulationFromCPointer(int* population, int* adjMatrix, int popSize, int indivSize){
	shared_ptr<Population>(new Population(population, adjMatrix, popSize, indivSize));
}
