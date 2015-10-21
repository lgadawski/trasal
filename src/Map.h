#ifndef MAP_H_
#define MAP_H_

#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include "BitsUtil.h"
#include "Individual.h"

using namespace std;



/** klasa reprezentująca mapę miast węzły (mneiasta) są reprezentowane w postaci binarnej.
 * Krawędzie łączące są przechowywa ne w tablicy dwuwymiarowej
 *
 */
class Map {
private:

	int mapSize;
	int num_bits;
	map<pair<City, City >, int> cityDistanceMap;
	set<City> citySet;
public:
	typedef pair<City, City> pair_of_cityies;


	Map() :
			mapSize(0), num_bits(0) {
	}
	Map(int amapSize) :
			mapSize(amapSize),
			num_bits(BitsUtil::GetNumberOfBitsNeedToRepresentValue(amapSize)) {
	}

	void AddCity(int id, int lowestPossibleDistance,
			int highestPossibleDistance);
	int GetMapSize() {
		return mapSize;
	}
	int GetNumbBits() {
		return num_bits;
	}

	static shared_ptr<Map>  ConstructMapOfSize(int mapSize, int lowestPossibleDistance,
			int highestPossibleDistance);

	string toString();
};

#endif /* MAP_H_ */
