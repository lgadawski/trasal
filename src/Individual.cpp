#include "Individual.h"
#include <math.h>
#include <algorithm>

using namespace boost;
using namespace std;

Individual::Individual(const shared_ptr<Map> spm){
	// tworze kopie miast do wektora.
	set<City> city_set = spm.get()->getCitySet();
	vector<City> cities_copy(city_set.begin(), city_set.end());

	while(!cities_copy.empty()){
		int index = randomutils::RandBetween(0,cities_copy.size()-1);
		vector<City>::iterator i = next(cities_copy.begin(), index);
		City *n = new City(*i);
		path.push_back(*n);
		cities_copy.erase(i);
	}

	cout << " result individual: ";	printutils::printPath(path);
}

long Individual::GetLength() const {
	if (length != -1) return length;
	length = 0;
	for(vector<City>::const_iterator it = path.begin(); it != path.end(); ++it) {
		vector<City>::const_iterator next_it = ++it;
		if (next_it != path.end()) {
			auto dist = map.get()->getDistanceBetween(*it, *next_it);
			length += dist;
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
		for(int i = 0; i<=path.size() ; i++){
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
	for (uint i = 0 ; i < path.size(); i++) if (c == path[i]) return true;

	return false;
}

optional<shared_ptr<Individual>> Individual::RandomlyMutate(double mutatePropability) const {
	int propabilityInPercents = mutatePropability * 100;

	shared_ptr<Individual> new_individual(new Individual(*this));
	uint path_size = path.size();
	for (uint i = 0; i < path_size; ++i) {
		cout << "current idx: " << i << endl;
		if (randomutils::RandBetween(0, 100) < propabilityInPercents) {
			auto first_idx = randomutils::RandBetween(0, path_size - 1);
			auto sec_idx = randomutils::RandBetween(0, path_size - 1);
			// jeśli drugi zostałby wylosowany tym samym
			while (first_idx == sec_idx) sec_idx = randomutils::RandBetween(0, path_size - 1);

			cout << "#mutate#" << " first_idx: " << first_idx << " second_idx: " << sec_idx << endl;

			new_individual.get()->swap_path(first_idx, sec_idx);
		}
	}
	if (this == new_individual.get()) {
		// none bits mutated, so no new individual has been created
		return none;
	}

	return optional<shared_ptr<Individual>>(new_individual);
}

void Individual::resetPath(){
	for(uint i = 0 ; i < path.size() ; i++){
		path[i]= City();
	}
}

int main_() {
	shared_ptr<Map> map = shared_ptr<Map>(Map::ReadMapFromFile("conf/mapa.txt"));
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

	auto mutant = i1.RandomlyMutate(0.5);
	cout << endl << "parent: " << i1 << endl;
	cout << endl << "mutant: " << *(mutant.get()) << endl;

	return 0;
}
