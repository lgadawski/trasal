#include "Individual.h"
#include <math.h>

using namespace boost;
using namespace std;

Individual::Individual(const shared_ptr<Map> spm){
	int num_bit_per_city = spm->getNumbBits();
	int num_of_cities = spm->getMapSize();

	// tworze kopie miast do wektora.
	vector<City> cities_copy(num_of_cities);
	std::copy(spm->getCitySet().begin(), spm->getCitySet().end(), cities_copy.begin());

	srand(time(0));
	int start_cities_number = cities_copy.size();
	for(int i = 0 ;  i <  start_cities_number; i++){
		//losuje nr it-tego miasta które mam wrzucic na listę
		int city_nr = randomutils::RandBetween(0, cities_copy.size());
		// wrzucam wylosowane misto do listy
		path.push_back(cities_copy[city_nr]);

		vector<City>::iterator it = cities_copy.begin();
		//usuwam miasto z wektora pomocniczego, zeby nie bylo duplikatow
		cities_copy.erase(next(it, city_nr));
	}
	for(list<City>::iterator it = path.begin() ; it != path.end() ; it++){
		cout<<"CL: "<< it->getId()<<" - "<<it->toStringBinary()<<endl;
	}

	binary_repr = boost::dynamic_bitset<>(num_bit_per_city*num_of_cities);
	int count = 0;
	for(list<City>::iterator it =path.begin(); it!= path.end(); it++){
		int city_bin_size = spm->getNumbBits();
		for(int i = 0; i< city_bin_size; i++){
			bool bit = it->getGenBit(i);
			if (bit){
				cout<<"1";
				cout.flush();
				binary_repr.set(count++);
			}else{
				cout<<"0";cout.flush();
				binary_repr.reset(count++);
			}
		}
		cout<<" ";
	}
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

boost::optional<std::shared_ptr<pair<Individual,Individual>>> Individual::RandomlyCrossover(const double crossoverProbability , Individual second){
	cout<<"Se - "<<bitutils::ToStringBitSet(this->GetBinaryReprezentation())<<endl;
	cout<<"Se - "<<bitutils::ToStringBitSet(second.GetBinaryReprezentation())<<endl;
	int multiplier = 1000;
	int crossoverInPromiles = crossoverProbability*multiplier;
	if(randomutils::RandBetween(0,crossoverInPromiles) < crossoverInPromiles){
		shared_ptr<Individual> new_individual_1(new Individual(*this));
		shared_ptr<Individual> new_individual_2(new Individual(second));
		int numOfbitsPerCity = this->GetPath().begin()->getNumOfBits();
		do{
			int separateIndex = randomutils::RandBetween(0, second.GetBinaryReprezentation().size()-2);
			uint size = second.GetBinaryReprezentation().size();
			for(uint i = 0 ; i< size; i++){
				bool bit1 = this->GetBit(i);
				bool bit2 = second.GetBit(i);
				if(i<=separateIndex){
					new_individual_1->SetBit(i, bit2);
					new_individual_2->SetBit(i, bit1);
				}
			}
			if(IsCorrectIndividual(new_individual_1) && IsCorrectIndividual(new_individual_2)){
				new_individual_1->SetPath(this->GetBinaryReprezentation(), numOfbitsPerCity);
				new_individual_2->SetPath(second.GetBinaryReprezentation(), numOfbitsPerCity);
			}
		}while(!IsCorrectIndividual(new_individual_1) || !IsCorrectIndividual(new_individual_2));
		return shared_ptr<pair<Individual,Individual>>(new pair<Individual, Individual>(*(new_individual_1.get()), *(new_individual_2.get())));
	}
	return none;
}

optional<shared_ptr<Individual>> Individual::RandomlyMutate(const double mutatePropability) const {
	int propabilityInPercents = mutatePropability * 100;
	cout << "mutatate prop: " << propabilityInPercents << " % " << endl;

	auto new_chromosome = boost::dynamic_bitset<>(binary_repr);
	shared_ptr<Individual> new_individual(new Individual());
	do {
		for (uint i = 0; i < new_chromosome.size(); ++i) {
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
void Individual::SetBinaryRepr(dynamic_bitset<> repr) {
	binary_repr = dynamic_bitset<>(repr);
}

void Individual::SetPath(boost::dynamic_bitset<> binary, int numOfBitsPerCity){
	for(uint i = 0 ; i<binary.size(); ){
		cout<<"Binary:"<<bitutils::ToStringBitSet(binary)<<endl;
		dynamic_bitset<> bcity(numOfBitsPerCity);
		for(int j = 0 ; j < numOfBitsPerCity ; j++, i++){
			bcity[j] = binary[i];
		}
		int icity=-1;
		binary>>icity;
		cout<<"Bin City: "<<bcity<<endl;
		cout<<"Int City: "<<icity<<endl;
		City c(icity, numOfBitsPerCity);
		this->path.push_back(c);
	}
}

int main() {
	shared_ptr<Map> map = shared_ptr<Map>(Map::ConstructMapOfSize(6, 1, 4));
	Individual i1(map);
	Individual i2(map);
	cout<<endl;
	cout<<"I1 - "<<bitutils::ToStringBitSet(i1.GetBinaryReprezentation())<<endl;
	cout<<"I2 - "<<bitutils::ToStringBitSet(i2.GetBinaryReprezentation())<<endl;
//	i1.SetBinaryRepr("00000111110000011111");


	auto mutant = i1.RandomlyCrossover(0.5, i2);

	cout << endl << "binary repr 1: " << mutant.get().get()->first.GetBinaryReprezentation() << endl;
	cout << endl << "binary repr 2: " << mutant.get().get()->first.GetBinaryReprezentation() << endl;
}
