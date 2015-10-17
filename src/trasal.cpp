#include <iostream>
#include "Configuration.h"
#include "Individual.h"
#include "Map.h"

using namespace std;

int main() {
	Configuration conf = Configuration::ReadFromFile("conf/app.properties");

	cout << "ps: " << conf.GetPopulationSize() << " poc: " << conf.GetPropabilityOfCrossover()
			<< " pom: " << conf.GetPropabilityOfMutation() << endl;

	const int mapSize = 4;

	Map map = Map::ConstructMapOfSize(mapSize);

	cout << "X: " << map.GetMapSize() << " " << map.GetNumbBits() << endl;

	return 0;
}
