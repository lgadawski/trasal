#ifndef MAP_H_
#define MAP_H_

#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>

#include "City.h"
#include "utils.h"

/**
 * Klasa reprezentująca mapę miast węzły (miasta) są reprezentowane w postaci binarnej.
 * Krawędzie łączące są przechowywane w mapie.
 *
 */
class Map {
private:
	int mapSize;
	std::set<City> citySet;
	std::map<std::pair<City, City >, int> cityDistanceMap;

	int calcNumOfBitsforIndividual();
	static std::vector<int> parseIntTabLine(std::string line);

public:
	typedef std::pair<City, City> pair_of_cityies;

	Map() :
			mapSize(0) {}
	Map(int amapSize) :
			mapSize(amapSize) {}

	virtual ~Map() {
		std::cout << " ~map ";
	}

	void AddRandomCity(int id, int lowestPossibleDistance, int highestPossibleDistance);
	int getMapSize() { return citySet.size(); }

	static std::shared_ptr<Map>  ConstructMapOfSize(int mapSize,
													int lowestPossibleDistance,
													int highestPossibleDistance);

	std::string ToString();
	int getDistanceBetween(const City & c1, const City & c2);

	void print() {
		std::cout << std::endl << std::endl << "map size: " << getMapSize() << std::endl;
		std::cout<<"nodes:";
		for(std::set<City>::iterator it = citySet.begin() ; it !=citySet.end() ; it++){
			std::cout<<*it<<" ";
		}
		std::cout << std::endl;
		for (const auto &p : cityDistanceMap) {
			std::cout << "m[" << "first city: " << p.first.first;
			std::cout << " sec city: " << p.first.second << "] = " << p.second << '\n';
		}
		std::cout << std::endl << std::endl;
	}

	const std::set<City> getCitySet() const {
		return citySet;
	}
	void AddCity(City c){citySet.insert(c);}
	void AddEdge(std::pair<std::pair<City, City>, int> edge){cityDistanceMap.insert(edge);};

	static bool WriteMapToFile(std::string path, Map& m);
	static std::shared_ptr<Map> ReadMapFromFile(std::string path);
};

#endif /* MAP_H_ */
