#ifndef MAP_H_
#define MAP_H_

#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include "BitsUtil.h"
#include "City.h"

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
	int calcNumOfBitsforIndividual();
public:
	typedef pair<City, City> pair_of_cityies;

	Map() :
			mapSize(0), num_bits(0) {
	}
	Map(int amapSize) :
			mapSize(amapSize),
			num_bits(BitsUtil::GetNumberOfBitsNeedToRepresentValue(amapSize-1)) {
	}

	void AddCity(int id, int lowestPossibleDistance,
			int highestPossibleDistance);
	int getMapSize() {
		return mapSize;
	}

	int getNumbBits() {
		return num_bits;
	}
	int getSizeInBits(){
		return getMapSize()*getNumbBits();
	}
	static shared_ptr<Map>  ConstructMapOfSize(int mapSize, int lowestPossibleDistance,
			int highestPossibleDistance);

	string toString();

	const set<City>& getCitySet() const {
		return citySet;
	}

	void setCitySet(const set<City>& citySet) {
		this->citySet = citySet;
	}
};

#endif /* MAP_H_ */
