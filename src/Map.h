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

/** klasa reprezentująca mapę miast węzły (mneiasta) są reprezentowane w postaci binarnej.
 * Krawędzie łączące są przechowywa ne w tablicy dwuwymiarowej
 *
 */
class Map {
private:
	int mapSize;
	int num_bits;
	std::map<std::pair<City, City >, int> cityDistanceMap;
	std::set<City> citySet;
public:
	typedef std::pair<City, City> pair_of_cityies;

	Map() :
			mapSize(0), num_bits(0) {}
	Map(int amapSize) :
			mapSize(amapSize),
			num_bits(bitutils::GetNumberOfBitsNeedToRepresentValue(amapSize)) {}

	void AddCity(int id, int lowestPossibleDistance, int highestPossibleDistance);
	int GetDistance(City&, City&);
	int GetMapSize() { return mapSize; }
	int GetNumbBits() { return num_bits; }

	static std::shared_ptr<Map>  ConstructMapOfSize(int mapSize,
													int lowestPossibleDistance,
													int highestPossibleDistance);

	std::string toString();
	void print() {
		std::cout << "map size: " << GetMapSize() << std::endl;
		std::cout << "number of bits needed: " << GetNumbBits() << std::endl;

		std::map<std::pair<City, City>, int>::iterator it;
		for (it = cityDistanceMap.begin(); it != cityDistanceMap.end(); ++it) {
			std::cout << "src city id: " << it->first.first.GetChromosome() ;
			std::cout << " dest city gen: " << it->first.second.GetChromosome();
			std::cout << " DIST: " << it->second << std::endl;
		}
	}
};

#endif /* MAP_H_ */
