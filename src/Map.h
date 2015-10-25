#ifndef MAP_H_
#define MAP_H_

#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>

#include "Bitutils.h"
#include "City.h"

/**
 * Klasa reprezentująca mapę miast węzły (miasta) są reprezentowane w postaci binarnej.
 * Krawędzie łączące są przechowywane w mapie.
 *
 */
class Map {
private:
	int mapSize;
	int num_bits;
	std::map<std::pair<City, City >, int> cityDistanceMap;
	std::set<City> citySet;
	int calcNumOfBitsforIndividual();
public:
	typedef std::pair<City, City> pair_of_cityies;

	Map() :
			mapSize(0), num_bits(0) {}
	Map(int amapSize) :
			mapSize(amapSize),
			num_bits(bitutils::GetNumberOfBitsNeedToRepresentValue(amapSize)) {}

	void AddCity(int id, int lowestPossibleDistance, int highestPossibleDistance);
	int getDistance(const City&, const City&) const;
	int getMapSize() { return mapSize; }
	int getNumbBits() { return num_bits; }

	static std::shared_ptr<Map>  ConstructMapOfSize(int mapSize,
													int lowestPossibleDistance,
													int highestPossibleDistance);

	std::string toString();
	void print() {
		std::cout << "map size: " << getMapSize() << std::endl;
		std::cout << "number of bits needed: " << getNumbBits() << std::endl;

		std::map<std::pair<City, City>, int>::iterator it;
		for (it = cityDistanceMap.begin(); it != cityDistanceMap.end(); ++it) {
			std::cout << "src city id: " << it->first.first.getGen() ;
			std::cout << " dest city gen: " << it->first.second.getGen();
			std::cout << " DIST: " << it->second << std::endl;
		}
	}


	int getSizeInBits(){
		return getMapSize()*getNumbBits();
	}

	const std::set<City>& getCitySet() const {
		return citySet;
	}
};

#endif /* MAP_H_ */
