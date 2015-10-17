#include "Map.h"

void Map::AddCity(int id) {
	City *c = new City(num_bits, id);
	citySet.insert(*c);
}
