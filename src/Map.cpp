#include "Map.h"
#include <math.h>
using namespace std;

void Map::AddCity(int id, int lowestPossibleDistance,
		int highestPossibleDistance) {
	City *c = new City(this->num_bits, id);
	City x();
	for(set<City>::iterator it = citySet.begin(); it!= citySet.end(); it++){
		int distance = (rand()%abs(highestPossibleDistance - lowestPossibleDistance))+lowestPossibleDistance;
		pair<City, City> *pcc = new pair<City, City>(*it, *c);
		cityDistanceMap.insert(pair<pair<City, City>, int>(*pcc, distance));
	}

	citySet.insert(*c);

}

Map& Map::ConstructMapOfSize(int mapSize, int lowestPossibleDistance = 0, int highestPossibleDistance = 200) {
	Map *map = new Map(mapSize);
	for (int var = 0; var < mapSize; ++var) {
		map->AddCity(var, lowestPossibleDistance, highestPossibleDistance);
	}
	return *map;
}
