#include "Map.h"

using namespace std;

void Map::AddCity(int id) {
	City *c = new City(num_bits, id);

	for_each(citySet.begin(),
			 citySet.end(),
			 [](City city) {
//		cityDistanceMap.insert(pair<City, City>(city, c), 2);
	});

	citySet.insert(*c);


}
