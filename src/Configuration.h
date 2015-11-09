#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Map.h"

const std::string SEPARATOR = "=";
const std::string POP_SIZE = "population_size";
const std::string PROP_OF_CROSS = "propability_of_crossover";
const std::string PROP_OF_MUT = "propability_of_mutation";

class Configuration {
private:
	int populationSize;
	double propabilityOfCrossover;
	double propabilityOfMutation;
public:
	Configuration() :
			populationSize(200), propabilityOfCrossover(0.25), propabilityOfMutation(
					0.01) {
	}

	Configuration(const int apopulationSize,
			const double apropabilityOfCrossover,
			const double aprobalityOfMutation) :
			populationSize(apopulationSize), propabilityOfCrossover(
					apropabilityOfCrossover), propabilityOfMutation(
					aprobalityOfMutation) {
	}

	int GetPopulationSize() const {
		return populationSize;
	}
	double GetPropabilityOfCrossover() const {
		return propabilityOfCrossover;
	}
	double GetPropabilityOfMutation() const {
		return propabilityOfMutation;
	}

	void SetPopulationSize(int ps) {
		populationSize = ps;
	}
	void SetPropabilityOfCrossover(double poc) {
		propabilityOfCrossover = poc;
	}
	void SetPropabilityOfMutation(double pom) {
		propabilityOfMutation = pom;
	}

	static Configuration& ReadFromFile(std::string file_name);

	void print() {
		std::cout << "popultion size: " << GetPopulationSize() << std::endl;
		std::cout << "propability of crossover: " << GetPropabilityOfCrossover()
				<< std::endl;
		std::cout << "propability of mutation: " << GetPropabilityOfMutation()
				<< std::endl;
	}
};

#endif
