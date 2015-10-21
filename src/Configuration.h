#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>
#include <fstream>
#include "Map.h"
using namespace std;

const string SEPARATOR = "=";
const string POP_SIZE = "population_size";
const string PROP_OF_CROSS = "propability_of_crossover";
const string PROP_OF_MUT = "propability_of_mutation";

class Configuration {

private:
	int populationSize;
	double propabilityOfCrossover;
	double propabilityOfMutation;

public:
	Configuration() :
		populationSize(50),
		propabilityOfCrossover(0.25),
		propabilityOfMutation(0.01) {}

	Configuration(int apopulationSize, double apropabilityOfCrossover, double aprobalityOfMutation) :
		populationSize(apopulationSize),
		propabilityOfCrossover(apropabilityOfCrossover),
		propabilityOfMutation(aprobalityOfMutation) {}

	int GetPopulationSize() { return populationSize; }
	double GetPropabilityOfCrossover() { return propabilityOfCrossover; }
	double GetPropabilityOfMutation() { return propabilityOfMutation; }

	void SetPopulationSize(int ps) { populationSize = ps; }
	void SetPropabilityOfCrossover(double poc) { propabilityOfCrossover = poc; }
	void SetPropabilityOfMutation(double pom) { propabilityOfMutation = pom; }

	static Configuration& ReadFromFile(string file_name);

	static bool WriteMapToFile(string path, Map& m);
};

#endif
