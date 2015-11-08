#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <memory>
#include <iostream>
#include <stdlib.h>
#include "Configuration.h"
#include "Individual.h"
#include "Map.h"
#include "GeneticAlgorithm.h"
#include "Population.h"

using namespace std;

int main(int ac, char* av[]) {
	Configuration conf = Configuration::ReadFromFile("conf/app.properties");
	cout << " POPULATION SIZE: " << conf.GetPopulationSize() << endl;

	auto map = shared_ptr<Map>(Map::ConstructMapOfSize(5, 1, 10));
//	auto map = shared_ptr<Map>(Map::ReadMapFromFile("conf/mapa.txt"));
	map->print();

	GeneticAlgorithm g(map, conf);
	g.Perform();

	return 0;
}

int main_test(int ac, char* av[]) {
	Configuration conf = Configuration::ReadFromFile("conf/app.properties");
	cout << " POPULATION SIZE: " << conf.GetPopulationSize() << endl;

	auto map = shared_ptr<Map>(Map::ConstructMapOfSize(50, 1, 10));
//	auto map = shared_ptr<Map>(Map::ReadMapFromFile("conf/mapa.txt"));
	map.get()->print();

	City c1(0), c2(1);
	cout << endl << " DIST 0 -> 1 : " << map.get()->getDistanceBetween(c1, c2)
			<< endl;

	Individual i(map);
	cout << endl << " LENGTH: " << i.GetLength() << endl;

	cout << endl << " CREATE POPULATION ";
	Population *p = new Population(map, conf.GetPopulationSize());
	for (auto &a : p->GetIndividualList()) {
		cout << endl << a << " L: " << a.GetLength() << endl;
	}

	auto best = p->GetBestIndividual();
	cout << endl << "BEST: " << best;
	cout << endl << endl << "POPULATION SIZE: " << p->GetPopulationSize()
			<< endl << endl;

	return 0;
}

int main2(int ac, char* av[]) {
	//read command line arguments
	try {
		string inputPath, outputPath;
		bool randomFlag = false;

		po::options_description desc("Allowed options");
		desc.add_options()("help", "produce help message")("input, i",
				po::value<string>(), "this option specifies input file name")(
				"output, o", po::value<string>(),
				"this option specifies output file name")("random",
				po::value<int>(), "set random graph generation")("test",
				"testing option");

		po::variables_map vm;
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			cout << desc << "\n";
			return 0;
		}

		if (vm.count("test")) {
			cout << "\nStarting testing" << "\n";
			shared_ptr<Map> pm = Map::ReadMapFromFile("conf/mapa.txt");

			shared_ptr<Map> pmap(Map::ConstructMapOfSize(6, 10, 500));
			if (pmap) {
				shared_ptr<Map> sp_map(pmap);
				cout << sp_map->ToString() << endl;
				//testy losowej generacji individuala z mapy
				shared_ptr<Individual> sp_ind(new Individual(sp_map));
				//testy zapisu do pliku
				Map::WriteMapToFile("conf/mapa.txt", *sp_map);
			}

			return 0;
		}

		if (vm.count("random")) {
			randomFlag = true;
			cout << "Random graph generation was set." << "\n";
		}

		if ((vm.count("i") + vm.count("o")) == 2) {
			cout << "Input file was set to " << vm["i"].as<string>() << ".\n";
			cout << "Output file was set to " << vm["o"].as<string>() << ".\n";

			if (randomFlag) {
				if (vm["random"].empty()) {
					cout
							<< "-random flag requires a value.(ex: ./trasal -random=8)"
							<< endl;
					return -1;
				}
				// here random graph generation happens

				// here saving generated graph to input file

				// here should be generating solution via genetic algorithm

				// here saving solution to output file
			} else {
//        		shared_ptr<Map> pm = Configuration::ReadMapFromFile(vm["i"].as<string>());
			}
		} else {
			cout
					<< "Input or output file was not set and they are mandatory for this program to work.\n";
		}

	} catch (exception& e) {
		cerr << "error: " << e.what() << "\n";
		return 1;
	} catch (...) {
		cerr << "Exception of unknown type!\n";
	}

	return 0;
}
