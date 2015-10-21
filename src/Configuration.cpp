#include "Configuration.h"
#include "Map.h"
#include <fstream>
#include <sstream>
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

vector<int> Configuration::parseIntTabLine(string line){
	stringstream ss;
	vector<int> v;
	size_t tab = line.find("\t");
	while(tab != string::npos){
		tab = line.find("\t");
		//ostatnia cyfra w linii
		if(tab == string::npos){
			string slastdigit = line.substr(0,line.size());
			ss<<slastdigit;
			int lastVertex = -1;
			ss>>lastVertex;
			v.push_back(lastVertex);
			break;
		}
		string sdigit = line.substr(0,tab);
		ss<<sdigit;
		int vertex=-1;
		ss>>vertex;
		v.push_back(vertex);
		ss.flush().clear();

		line=line.substr(tab+1, line.size()-tab);
	}
	return v;
}

shared_ptr<Map> Configuration::ReadMapFromFile(string path){
	ifstream ifs(path.c_str());
	if(ifs.is_open()){
		//pierwsza linia
		unique_ptr<char> abuf(new char[512]);
		ifs.getline(abuf.get(), 512);
		string firstLine(abuf.get());

		vector<int> v = parseIntTabLine(firstLine);

		//reszta linii
		vector<vector <int> > edges;
		while(!ifs.eof()){
			unique_ptr<char> lbuf(new char[64]);
			ifs.getline(lbuf.get(), 64);
			string line(lbuf.get());
			edges.push_back(parseIntTabLine(line));
		}

		return shared_ptr<Map>(new Map(/*v, edges*/));
	}else{
		cout<<"Unnable to open file to read."<<endl;
	}
	return shared_ptr<Map>();
}

