#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <memory>
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

//	shared_ptr<Map> pmap = Map::ConstructMapOfSize(mapSize, 0, 200);

//	cout << "X: " << pmap->GetMapSize() << " " << pmap->GetNumbBits() << endl;

	//read command line arguments
	try {
	 	string inputPath, outputPath;
	  	bool randomFlag = false;


	    po::options_description desc("Allowed options");
	    desc.add_options()
	      	("help", "produce help message")
	        ("input, i", po::value<string>(), "this option specifies input file name")
	        ("output, o", po::value<string>(), "this option specifies output file name")
			("random", po::value<int>(),"set random graph generation")
			("test", "testing option")
	    ;

	    po::variables_map vm;
	    po::store(po::parse_command_line(ac, av, desc), vm);
	    po::notify(vm);

	    if (vm.count("help")) {
	        cout << desc << "\n";
	        return 0;
	    }

	    if(vm.count("test")){
	    	cout<< "\nStarting testing"<<"\n";
//	    	shared_ptr<Map> pm = Configuration::ReadMapFromFile("conf/mapa.txt");


	    	shared_ptr<Map> pmap(Map::ConstructMapOfSize(6, 10, 500));
	    	if(pmap){
	    		shared_ptr<Map> sp_map(pmap);
	    		cout<<sp_map->toString()<<endl;
	    		//testy losowej generacji individuala z mapy
	    		shared_ptr<Individual> sp_ind(new Individual(sp_map));
	    		//testy zapisu do pliku
//	    		Configuration::WriteMapToFile("conf/mapa.txt",*sp_map);
	    	}

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
	        	if(vm["random"].empty()){
	        	cout<<"-random flag requires a value.(ex: ./trasal -random=8)"<<endl;
	        	return -1;
	        	}
	        	// here random graph generation happens

	        	// here saving generated graph to input file

	        	// here should be generating solution via genetic algorithm

	        	// here saving solution to output file
        	}else{
        		shared_ptr<Map> pm = Configuration::ReadMapFromFile(vm["i"].as<string>());
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
