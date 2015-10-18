#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include "Configuration.h"
#include "Individual.h"
#include "Map.h"

using namespace std;

int main(int ac, char* av[]) {

	// read configuration file
	Configuration conf = Configuration::ReadFromFile("conf/app.properties");

	cout << "ps: " << conf.GetPopulationSize() << " poc: " << conf.GetPropabilityOfCrossover()
			<< " pom: " << conf.GetPropabilityOfMutation() << endl;

	const int mapSize = 4;

	Map map = Map::ConstructMapOfSize(mapSize);

	cout << "X: " << map.GetMapSize() << " " << map.GetNumbBits() << endl;

	//read command line arguments
	try {
	 	string inputPath, outputPath;
	  	bool randomFlag = false;


	    po::options_description desc("Allowed options");
	    desc.add_options()
	      	("help", "produce help message")
	        ("i", po::value<string>(), "this option specifies input file name")
	        ("o", po::value<string>(), "this option specifies output file name")
			("random", "set random graph generation")
	    ;

	    po::variables_map vm;
	    po::store(po::parse_command_line(ac, av, desc), vm);
	    po::notify(vm);

	    if (vm.count("help")) {
	        cout << desc << "\n";
	        return 0;
	    }

	    if (vm.count("random")){
	      	randomFlag = true;
	       	cout<< "Random graph generation was set." << "\n";
	    }

	    if ((vm.count("i") +vm.count("o")) ==2 ) {
	        cout << "Input file was set to " << vm["i"].as<string>() << ".\n";
	        cout << "Output file was set to " << vm["o"].as<string>() << ".\n";

	        if(randomFlag){
           	// here random graph generation happens

          	// here saving generated graph to input file

           	// here should be generating solution via genetic algorithm

           	// here saving solution to output file
        	}else{

        	}
	    } else {
	        cout << "Input or output file was not set and they are mandatory for this program to work.\n";
	    }

	}
	catch(exception& e) {
	    cerr << "error: " << e.what() << "\n";
	    return 1;
	}
	catch(...) {
	    cerr << "Exception of unknown type!\n";
	}

	return 0;
}