#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>
#include <fstream>

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

	static Configuration& ReadFromFile(string file_name) {
		Configuration *c = new Configuration();
		ifstream file(file_name.c_str());
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				string param_name = line.substr(0, line.find(SEPARATOR));
				string value = line.erase(0, line.find(SEPARATOR) + SEPARATOR.length());
				cout << param_name << " = " << value << " " << endl;
				if (POP_SIZE.compare(param_name)) c->SetPopulationSize(stoi(value));
				if (PROP_OF_CROSS.compare(param_name)) c->SetPropabilityOfCrossover(stod(value));
				if (PROP_OF_MUT.compare(param_name)) c->SetPropabilityOfMutation(stod(value));
			}
			file.close();
		}

		return *c;
	}
};

#endif
