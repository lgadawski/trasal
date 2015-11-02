#include "Configuration.h"
#include <sstream>
#include <string>

using namespace std;

 Configuration& Configuration::ReadFromFile(string file_name){
		Configuration *c = new Configuration();
		ifstream file(file_name.c_str());
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				string param_name = line.substr(0, line.find(SEPARATOR));
				string value = line.erase(0, line.find(SEPARATOR) + SEPARATOR.length());
				if (POP_SIZE.compare(param_name) == 0) c->SetPopulationSize(stoi(value));
				if (PROP_OF_CROSS.compare(param_name) == 0) c->SetPropabilityOfCrossover(stod(value));
				if (PROP_OF_MUT.compare(param_name) == 0) c->SetPropabilityOfMutation(stod(value));
			}
			file.close();
		}

		return *c;
	}
