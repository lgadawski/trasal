#include "Map.h"
#include "City.h"
#include "Bitutils.h"
#include <math.h>
#include <memory>
#include <set>
#include <sstream>

using namespace std;

void Map::AddCity(int id, int lowestPossibleDistance,
		int highestPossibleDistance) {
	//tworze nowe miasto
	City* cp = new City(id, bitutils::GetNumberOfBitsNeedToRepresentValue(id));
	srand(time(0));
	for(set<City>::iterator it = citySet.begin(); it!= citySet.end(); it++){
		int distance = (rand()%abs(highestPossibleDistance - lowestPossibleDistance))+lowestPossibleDistance;
		City existing_city = *it;
		cityDistanceMap.insert(pair<pair_of_cityies, int>(pair_of_cityies(*cp, existing_city),distance));
	}
	citySet.insert(*cp);

}


shared_ptr<Map> Map::ConstructMapOfSize(int mapSize, int lowestPossibleDistance = 0, int highestPossibleDistance = 200) {
	shared_ptr<Map> pmap(new Map(mapSize));
	for (int var = 0; var < mapSize; ++var) {
		pmap->AddCity(var, lowestPossibleDistance, highestPossibleDistance);
	}
	return pmap;
}

string Map::toString(){
	string vertexes;
	stringstream ss;
	for(set<City>::iterator it = citySet.begin() ; it != citySet.end() ; it++){
		ss<<it->getId();
		string temp;
		ss>>temp;
		ss.flush().clear();
		vertexes.append(temp);
		if(next(it,1)!=citySet.end())
			vertexes.append("\t");

	}
	vertexes.append("\n");

	ss.flush();
	ss.clear();

	string edges;
	for(map<pair<City, City>, int>::iterator it = cityDistanceMap.begin() ; it != cityDistanceMap.end() ; it++){
		ss<<it->first.first.getId();
		string temp;

		ss>>temp;
		ss.flush().clear();
		edges.append(temp).append("\t");
		ss<<it->first.second.getId();
		ss>>temp;
		ss.flush().clear();
		edges.append(temp).append("\t");
		ss<<it->second;
		ss>>temp;
		ss.flush().clear();
		edges.append(temp).append("\n");
	}

	vertexes.append(edges);
//	cout<<"ALL: "<<vertexes;
	return vertexes;
}

int Map::getDistance(City& src, City& dest) {
	auto it = cityDistanceMap.find(pair<City, City>(src, dest));
	if (it != cityDistanceMap.end()) {
		return it->second;
	}
	it = cityDistanceMap.find(pair<City, City>(dest, src));
	if (it != cityDistanceMap.end()) {
		return it->second;
	}

	throw exception();
}
