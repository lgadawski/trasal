#include "Configuration.h"
#include "Map.h"
#include <fstream>

using namespace std;

 Configuration& Configuration::ReadFromFile(string file_name){
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

bool Configuration::WriteMapToFile(string path, Map& m){
	ofstream ofs(path.c_str());
	if (ofs.is_open()){
		cout<<"Otwarte"<<endl;
		ofs<<m.toString();
	}
	ofs.close();
	return true;
}
