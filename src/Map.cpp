#include "Map.h"
#include "City.h"
#include <math.h>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "utils.h"

using namespace std;

Map::Map(int* popul, int* adjMatrix, int populSize, int indSize){
	for (uint i = 0; i < indSize; i++) {
				this->AddCity(City(i));
	}
	for (uint i = 0; i < indSize; i++) {
		for (uint p = 0; p < indSize;p++) {
			pair<City, City> cp(i, p);
			int edgeWeight = adjMatrix[i*indSize+p];
			pair<pair<City, City>, int> edge(cp, edgeWeight);
			this->AddEdge(edge);

		}
	}
}

shared_ptr<Map> Map::ReadMapFromFile(string path) {
	ifstream ifs(path.c_str());
	if (ifs.is_open()) {
		shared_ptr<Map> spm(new Map());
		//pierwsza linia, ta z miastami
		unique_ptr<char> abuf(new char[512]);
		ifs.getline(abuf.get(), 512);
		string firstLine(abuf.get());

		vector<int> v = parseIntTabLine(firstLine);
		for (uint i = 0; i < v.size(); i++) {
			spm->AddCity(City(v[i]));
		}
		//reszta linii, czymi krawędzie, 1krawedz == 1 linia
		vector<vector<int> > edges;
		while (!ifs.eof()) {
			unique_ptr<char> lbuf(new char[64]);
			ifs.getline(lbuf.get(), 64);
			string line(lbuf.get());
			edges.push_back(parseIntTabLine(line));
		}
		for (uint i = 0; i < edges.size(); i++) {
			if (!edges[i].empty()) {
//				cout << edges[i][0] << edges[i][1] << edges[i][2] << endl;
				pair<City, City> cp(edges[i][0], edges[i][1]);
				pair<pair<City, City>, int> edge(cp, edges[i][2]);
				spm->AddEdge(edge);
			}
		}

		return spm;
	} else {
		cout << "Unnable to open file to read." << endl;
	}
	return shared_ptr<Map>();
}

vector<int> Map::parseIntTabLine(string line) {
	stringstream ss;
	vector<int> v;
	size_t tab = line.find("\t");
	while (tab != string::npos) {
		tab = line.find("\t");
		//ostatnia cyfra w linii
		if (tab == string::npos) {
			string slastdigit = line.substr(0, line.size());
			ss << slastdigit;
			int lastVertex = -1;
			ss >> lastVertex;
			v.push_back(lastVertex);
			break;
		}
		string sdigit = line.substr(0, tab);
		ss << sdigit;
		int vertex = -1;
		ss >> vertex;
		v.push_back(vertex);
		ss.flush().clear();

		line = line.substr(tab + 1, line.size() - tab);
	}
	return v;
}

bool Map::WriteMapToFile(string path, Map& m) {
	ofstream ofs(path.c_str());
	if (ofs.is_open()) {
		cout << "Otwarte" << endl;
		ofs << m.ToString();
	}
	ofs.close();
	return true;
}

void Map::AddRandomCity(int id, int lowestPossibleDistance,
		int highestPossibleDistance) {
	City *cp = new City(id);
	for (auto it = citySet.begin(); it != citySet.end(); ++it) {
		int distance = randomutils::RandBetween(lowestPossibleDistance,
				highestPossibleDistance);
		cityDistanceMap.insert(
				pair<pair_of_cityies, int>(pair_of_cityies(*cp, *it),
						distance));
	}
	citySet.insert(*cp);
}

shared_ptr<Map> Map::ConstructMapOfSize(int mapSize,
		int lowestPossibleDistance = 0, int highestPossibleDistance = 200) {
	shared_ptr<Map> pmap(new Map(mapSize));

	for (int var = 0; var < mapSize; ++var) {
		pmap->AddRandomCity(var, lowestPossibleDistance,
				highestPossibleDistance);
	}

	return pmap;
}

string Map::ToString() {
	string vertexes;
	stringstream ss;
	for (auto it = citySet.begin(); it != citySet.end(); it++) {
		ss << it->getId();
		string temp;
		ss >> temp;
		ss.flush().clear();
		vertexes.append(temp);
		if (next(it, 1) != citySet.end())
			vertexes.append("\t");

	}
	vertexes.append("\n");

	ss.flush();
	ss.clear();

	string edges;
	for (auto it = cityDistanceMap.begin();
			it != cityDistanceMap.end(); it++) {
		ss << it->first.first.getId();
		string temp;

		ss >> temp;
		ss.flush().clear();
		edges.append(temp).append("\t");
		ss << it->first.second.getId();
		ss >> temp;
		ss.flush().clear();
		edges.append(temp).append("\t");
		ss << it->second;
		ss >> temp;
		ss.flush().clear();
		edges.append(temp).append("\n");
	}

	vertexes.append(edges);
//	cout<<"ALL: "<<vertexes;
	return vertexes;
}

int Map::getDistanceBetween(const City & c1, const City & c2) {
	auto found = cityDistanceMap.find(pair<City, City>(c1, c2));
	if (found == cityDistanceMap.end()) {
		found = cityDistanceMap.find(pair<City, City>(c2, c1));
		if (found == cityDistanceMap.end()) {
			throw exception();
		}
	}

	return found->second;
}



