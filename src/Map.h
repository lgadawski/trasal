#ifndef MAP_H_
#define MAP_H_

#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include "BitsUtil.h"
#include "Individual.h"

using namespace std;

class Map {
private:
	int mapSize;
	int num_bits;
	map<pair<City, City>, int> cityDistanceMap;
	set<City> citySet;
public:
	Map() : mapSize(0), num_bits(0) {}
	Map(int amapSize) :
		mapSize(amapSize),
		num_bits(BitsUtil::GetNumberOfBitsNeedToRepresentValue(amapSize)) {}

	void AddCity(int id);
	int GetMapSize() { return mapSize; }
	int GetNumbBits() { return num_bits; }

	static Map& ConstructMapOfSize(int mapSize) {
		Map *map = new Map(mapSize);

		for (int var = 0; var < mapSize; ++var) {
			map->AddCity(var);
		}

		return *map;
	}
};

#endif /* MAP_H_ */
