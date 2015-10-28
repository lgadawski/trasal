#include "Individual.h"
#include "Configuration.h"
#include <math.h>

using namespace boost;
using namespace std;

Individual::Individual(const shared_ptr<Map> spm){
	int num_of_cities = spm->getMapSize();

	// tworze kopie miast do wektora.
	vector<City> cities_copy(num_of_cities);
	std::copy(spm->getCitySet().begin(), spm->getCitySet().end(), cities_copy.begin());

	cout<<"citCopy";
	printutils::printPath(cities_copy);//FIXME debug

	while(!cities_copy.empty()){
		vector<City>::iterator i;
		int index = randomutils::RandBetween(0,cities_copy.size()-1);
		i = next(cities_copy.begin(), index);
		printutils::printPath(cities_copy);
		path.push_back(*i);
		cities_copy.erase(i);//FIXME
		cout<<endl;
	}

}

long Individual::GetLength() const {
	if (length != -1) return length;
	length = 0;
	for(vector<City>::const_iterator it = path.begin(); it != path.end(); ++it) {
		vector<City>::const_iterator next_it = ++it;
		if (next_it != path.end()) {
			length += map.get()->getDistanceBetween(*it, *next_it);
		}
	}

	return length;
}

boost::optional<pair<Individual,Individual>> Individual::RandomlyCrossover(const double crossoverProbability , Individual second){
	//TODO po
	int multiplier = 1000;
	int crossoverInPromiles = crossoverProbability*multiplier;
	if(randomutils::RandBetween(0,crossoverInPromiles) < crossoverInPromiles){
		Individual new_individual_1 = Individual(*this);
		Individual new_individual_2 = Individual(second);
		cout<<"IND1 "<<new_individual_1<<endl;
		cout<<"IND2 "<<new_individual_2<<endl;
		new_individual_1.resetPath();
		new_individual_2.resetPath();

		int lesserSeparateIndex = randomutils::RandBetween(0,path.size()-1);
		int largerSeparateIndex = -1;
		do{
			largerSeparateIndex = randomutils::RandBetween(0,path.size()-1);
		}while(lesserSeparateIndex==largerSeparateIndex);

		if(largerSeparateIndex<lesserSeparateIndex){
			int temp = lesserSeparateIndex;
			lesserSeparateIndex = largerSeparateIndex;
			largerSeparateIndex = temp;
		}

		for(int i = lesserSeparateIndex ; i<=largerSeparateIndex ; i++){
			if(i>=lesserSeparateIndex && i<=largerSeparateIndex){	//jezeli jestem na posycji do wymiany kawałka pomiędzy i1 a i2
				new_individual_1.SetCity(i, second.GetCity(i));
				new_individual_2.SetCity(i, this->GetCity(i));
				cout<<new_individual_1<<endl;
				cout<<new_individual_2<<endl<<endl;
			}
		}
		for(int i = 0, j =0 ; i<=path.size() ; i++){
			if(i>=lesserSeparateIndex && i<=largerSeparateIndex){	//jezeli jestem na posycji do wymiany kawałka pomiędzy i1 a i2
				continue;
			}else{
				for(int j=0 ; j < path.size() ; j++){
					if(!new_individual_1.ContainsCity(this->GetCity(j))){
						new_individual_1.SetCity(i,this->GetCity(j));
						break;
					}
				}
				for(int j=0 ; j < path.size() ; j++){
					if(!new_individual_2.ContainsCity(second.GetCity(j))){
						new_individual_2.SetCity(i,second.GetCity(j));
						break;
					}
				}
			}
		}
		cout<<new_individual_1<<endl;
		cout<<new_individual_2<<endl<<endl;

		return pair<Individual,Individual>(new_individual_1,new_individual_2);
	}
	return none;
}

bool Individual::ContainsCity(City c){
	for(int i = 0 ; i < path.size() ; i++){
		if(c == path[i])
			return true;
	}
	return false;
}

optional<shared_ptr<Individual>> Individual::RandomlyMutate(const double mutatePropability) const {
/*	int propabilityInPercents = mutatePropability * 100;
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
	return none;*/
}



bool Individual::IsCorrectIndividual(const shared_ptr<Individual> new_individual) {
	// TODO sprawdzenie poprawności osobnika
	return true;
}

void Individual::resetPath(){
	for(uint i = 0 ; i < path.size() ; i++){
		path[i]= City();
	}
}


int main() {
	shared_ptr<Map> map = shared_ptr<Map>(Configuration::ReadMapFromFile("conf/mapa.txt"));
	map->print();
	Individual i1(map);
	cout<<"///////////////////////////"<<endl;
	Individual i2(map);
	cout<<endl;
	cout<<"IND1 "<<i1<<endl;
	cout<<"IND2 "<<i2<<endl;

	auto pr = i1.RandomlyCrossover(1, i2);
	cout << endl << "child 1: " << pr.get().first << endl;
	cout << endl << "child 2: " << pr.get().second << endl;


//	cout << endl << "binary repr 2: " << mutant.get().get()->first.GetBinaryReprezentation() << endl;
}
