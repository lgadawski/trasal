#include "Individual.h"
#include <math.h>

using namespace boost;
using namespace std;

Individual::Individual(const shared_ptr<Map> spm){
	int num_bit_per_city = spm->getNumbBits();
	int size = spm->getMapSize();
	// nie wiem jak miałbym w losowej kolejnosci generowac miasta do osobnika,
	// ale wiem jak to zrobic za pomocą wektora więc,
	// tworze kopie miast do wektora.
	vector<City> cities_copy(size);

	std::copy(spm->getCitySet().begin(), spm->getCitySet().end(), cities_copy.begin());

//	for(set<City>::iterator it = spm->getCitySet().begin() ; it != spm->getCitySet().end() ; it++){
//		cout<<"CS: "<< it->getId()<<" ";
//	}
//	cout<<endl;
//
//	for(vector<City>::iterator it = cities_copy.begin() ; it != cities_copy.end() ; it++){
//		cout<<"CV: "<< it->getId()<<" ";
//	}
//	cout<<endl;

	srand(time(0));
	int start_cities_number = cities_copy.size();
	for(int i = 0 ;  i <  start_cities_number; i++){
		//losuje nr it-tego miasta które mam wrzucic na listę
		int city_nr = rand()%cities_copy.size();
		// wrzucam wylosowane misto do listy
		path.push_back(cities_copy[city_nr]);

		vector<City>::iterator it = cities_copy.begin();
		//usuwam miasto z wektora pomocniczego, zeby nie bylo duplikatow
		cities_copy.erase(next(it, city_nr));
	}
	for(list<City>::iterator it = path.begin() ; it != path.end() ; it++){
		cout<<"CL: "<< it->getId()<<" ";
	}
	cout<<endl;
	binary_repr = boost::dynamic_bitset<>();
	for(list<City>::iterator it =path.begin(); it!= path.end(); it++){
		binary_repr.append(it->getId());
	}

//	for(int i = 0 ; i<binary_repr.size() ; i++){
//		cout<<binary_repr[i];
//	}
//	cout<<endl;
//	cout<<endl;

}

long Individual::GetLength() const {
	if (length != -1) return length;
	length = 0;
	for(list<City>::const_iterator it = path.begin(); it != path.end(); ++it) {
		list<City>::const_iterator next_it = ++it;
		if (next_it != path.end()) {
			length += map.get()->getDistance(*it, *next_it);
		}
	}

	return length;
}

optional<shared_ptr<Individual>> Individual::RandomlyMutate(const double mutatePropability) const {
	int propabilityInPercents = mutatePropability * 100;
	cout << "mutatate prop: " << propabilityInPercents << " % " << endl;

	auto new_chromosome = boost::dynamic_bitset<>(binary_repr);
	shared_ptr<Individual> new_individual(new Individual());
	do {
		for (int i = 0; i < new_chromosome.size(); ++i) {
			cout << "current idx: " << i << endl;
			if (randomutils::RandBetween(0, 100) < propabilityInPercents) {
				cout << "#mutate#" << endl;
				new_chromosome[i].flip();
			}
		}
		new_individual = shared_ptr<Individual>(new Individual(new_chromosome, map));
		if (new_chromosome == binary_repr) {
			// none bits mutated, so no new individual has been created
			return none;
		}
	} while (!IsCorrectIndividual(new_individual));

	return optional<shared_ptr<Individual>>(new_individual);
}

bool Individual::IsCorrectIndividual(const shared_ptr<Individual> new_individual) {
	// TODO sprawdzenie poprawności osobnika
	return true;
}

void Individual::SetBinaryRepr(string repr) {
	binary_repr = dynamic_bitset<>(repr);
}

int main() {
	shared_ptr<Map> map = shared_ptr<Map>(Map::ConstructMapOfSize(4, 1, 4));
	Individual i(map);
	i.SetBinaryRepr("00000111110000011111");
	cout << "binary repr: " << i.GetBinaryReprezentation() << endl;
	auto mutant = i.RandomlyMutate(0.5);
	cout << endl << "binary repr: " << mutant.get().get()->GetBinaryReprezentation() << endl;
}
