#include "GeneticAlgorithm.h"
#include <chrono>

Individual GeneticAlgorithm::Perform() {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
//	auto initialPopulation = shared_ptr<Population>(new Population(map, conf.GetPopulationSize()));

	int* initialPopulation = createPopulationFromMap(this->map.get(), conf.GetPopulationSize(), this->map->getMapSize());
	int* adjMatrix = createAdjMatrixFromMap(this->map);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
//	cout<<"Initial population initialization time: "<< duration<<" microseconds"<<endl;

	//start broadcast
	int popSize=conf.GetPopulationSize();
	int indSize=this->map->getMapSize();
	int* smallPulationInt=initialPopulation;
	int* adjMatrix2 = adjMatrix;
	//end broadcast

//	auto currentPopulation = initialPopulation->Reproduce();
	shared_ptr<Population> initialPopulationSP(new Population(smallPulationInt, adjMatrix2, popSize, indSize));
	auto currentPopulation = initialPopulationSP->Reproduce();
	auto whole_time = 0;
	for (int i = 0; i < GENERATION_NUMBER; ++i) {
//		cout << endl << "GA debug: " << i << endl;
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
//		auto absBestWorst = initialPopulation->
		currentPopulation = initialPopulationSP->Reproduce();

		currentPopulation->RandomlyCrossover(conf.GetPropabilityOfCrossover());
		currentPopulation->RandomlyMutate(conf.GetPropabilityOfMutation());

		initialPopulationSP = currentPopulation;
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
		whole_time += duration;

//		cout<<i<<" 'st generation production time: "<<duration<<" microseconds"<<endl;
	}

	cout << endl << "whole loop time " << whole_time << endl;

	auto best = initialPopulationSP.get()->GetBestIndividual();
	cout << endl << " END: ";
	printutils::printPath(best.GetPath());
	cout << endl << "PAth LEN: " << best.GetLength() << endl;

	return initialPopulationSP->GetBestIndividual();
}

int* GeneticAlgorithm::createPopulationFromMap(Map* mapa, int populationSize, int individualSize){
	int * population = new int[populationSize*individualSize];
	Population p(shared_ptr<Map>(mapa), populationSize);
//	cout<<p<<endl;
	int oneDpos = 0;
	for(int i = 0; i<p.GetIndividualList().size(); i++){
		Individual individual = p.GetIndividualList()[i];
		for(int j = 0; j<individual.GetPath().size(); j++){
			population[oneDpos] = individual.GetCity(j).getId();
			oneDpos++;
		}
	}

	cout<<"Population:"<<endl;
	for(int i = 0 ; i < individualSize*populationSize ; i++){
		if(i%individualSize==0){
			cout<<endl;
		}
		cout<<population[i]<<", ";
	}
	cout<<endl;
	return population;
}
int* GeneticAlgorithm::createAdjMatrixFromMap(shared_ptr<Map> map){
	int* adjMatrix = new int[map->getMapSize()*map->getMapSize()];
	int oneDpos=0;
	int matrixSize = map->getMapSize();
	cout<<" edges count "<< map->getAllEdgesMap().size()<<endl;
	for(auto const &elem : map->getAllEdgesMap()){
		int cityId1 = elem.first.first.getId();
		int cityId2 = elem.first.second.getId();
		int ind1 = cityId1*matrixSize +cityId2;
		int ind2 = cityId2*matrixSize +cityId1;
		adjMatrix[ind1] = elem.second;
		adjMatrix[ind2] = elem.second;
	}

	for(int i = 0 ; i < matrixSize ; i++){
		adjMatrix[i*matrixSize +i] = 0;
	}

	for(int i = 0 ; i < matrixSize*matrixSize ; i++){
		if(i%matrixSize==0){
			cout<<endl;
		}
		cout<<adjMatrix[i]<<", ";
	}
	cout<<endl;
	return adjMatrix;
}

shared_ptr<Population> GeneticAlgorithm::createPopulationFromCPointer(int* population, int* adjMatrix, int popSize, int indivSize){
	shared_ptr<Population>(new Population(population, adjMatrix, popSize, indivSize));
}
