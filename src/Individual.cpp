#include "Individual.h"
#include <math.h>
#include <algorithm>

using namespace boost;
using namespace std;

Individual::Individual(const shared_ptr<Map> spm) :
		map(spm) {
	// tworze kopie miast do wektora.
	set<City> city_set = spm.get()->getCitySet();
	vector<City> cities_copy(city_set.begin(), city_set.end());

	while (!cities_copy.empty()) {
		int index = randomutils::RandBetween(0, cities_copy.size() - 1);
		auto i = next(cities_copy.begin(), index);
		City *n = new City(*i);
		path.push_back(*n);
		cities_copy.erase(i);
	}
}

Individual::Individual(int* indPath, int indSize, shared_ptr<Map> m){
	this->map = m;
	this->cum_dist = 0;
	this->length = indSize;
	for(int i = 0 ; i<indSize ; i++){
		this->path.push_back(indPath[i]);
	}
	int dist = this->GetLength();
//	cout<<"Len: "<<dist<<endl;
	this->cum_dist = dist;
//	for(int i = 0 ; i<indSize-1 ; i++){
//			City c1(path[i]);
//			City c2(path[i+1]);
//			int dist = this->map->getDistanceBetween(c1,c2);
//			this->cum_dist += dist;
//	}

}

int* Individual::convertToIntBuffer(){
	int* buffer = new int[this->path.size()];
	for(int i = 0 ; i < this->path.size() ; i++){
		buffer[i] = this->path[i].getId();
	}
	return buffer;
}

long Individual::GetLength() const {
//	if (length != -1)
//		return length;
	length = 0;
	for (auto it = path.begin(); it != path.end();) {
		auto prev_it = it++;
		if (it != path.end()) {
			auto dist = map.get()->getDistanceBetween(*prev_it, *it);
			length += dist;
		}
	}
	length+=map.get()->getDistanceBetween(path.back(), path.front());

	return length;
}

boost::optional<pair<Individual, Individual>> Individual::RandomlyCrossover(
		const double crossoverProbability, Individual &second) {
	//TODO po
	int multiplier = 1000;
	int crossoverInPromiles = crossoverProbability * multiplier;
	if (randomutils::RandBetween(0, crossoverInPromiles) < crossoverInPromiles) {
		Individual new_individual_1 = Individual(*this);
		Individual new_individual_2 = Individual(second);
//		cout << "IND1 " << new_individual_1 << endl;
//		cout << "IND2 " << new_individual_2 << endl;
		new_individual_1.resetPath();
		new_individual_2.resetPath();

		int lesserSeparateIndex = randomutils::RandBetween(0, path.size() - 1);
		int largerSeparateIndex = -1;
		do {
			largerSeparateIndex = randomutils::RandBetween(0, path.size() - 1);
		} while (lesserSeparateIndex == largerSeparateIndex);

		if (largerSeparateIndex < lesserSeparateIndex) {
			int temp = lesserSeparateIndex;
			lesserSeparateIndex = largerSeparateIndex;
			largerSeparateIndex = temp;
		}

//		#pragma omp parallel for shared(lesserSeparateIndex, largerSeparateIndex)
		for (int i = lesserSeparateIndex; i <= largerSeparateIndex; i++) {
			//jezeli jestem na posycji do wymiany kawałka pomiędzy i1 a i2
			if (i >= lesserSeparateIndex && i <= largerSeparateIndex) {
				new_individual_1.SetCity(i, second.GetCity(i));
				new_individual_2.SetCity(i, GetCity(i));
//				cout << new_individual_1 << endl;
//				cout << new_individual_2 << endl << endl;
			}
		}

		const int path_size = (int) path.size();
		for (int i = 0; i <= path_size; i++) {
			//jezeli jestem na posycji do wymiany kawałka pomiędzy i1 a i2
			if (!(i >= lesserSeparateIndex && i <= largerSeparateIndex)) {
				bool should_break1 = false;
				for (int j = 0; j < path_size && !should_break1; j++) {
					auto j_city = GetCity(j);
					if (!new_individual_1.ContainsCity(j_city)) {
						new_individual_1.SetCity(i, j_city);
						should_break1 = true;
					}
				}

				bool should_break2 = false;
				for (int j = 0; j < path_size && !should_break2; j++) {
					auto j_city = second.GetCity(j);
					if (!new_individual_2.ContainsCity(j_city)) {
						new_individual_2.SetCity(i, j_city);
						should_break2 = true;
					}
				}
			}
		}
//		cout << new_individual_1 << endl;
//		cout << new_individual_2 << endl << endl;

		return pair<Individual, Individual>(new_individual_1, new_individual_2);
	}

	return none;
}

bool Individual::ContainsCity(City c) const {
	for (uint i = 0; i < path.size(); i++)
		if (c == path[i])
			return true;

	return false;
}

optional<shared_ptr<Individual>> Individual::RandomlyMutate(double mutatePropability) const {
	int propabilityInPercents = mutatePropability * 100;

	shared_ptr<Individual> new_individual(new Individual(*this));
	int path_size = path.size();

	for (int i = 0; i < (int) path_size; ++i) {
		if (randomutils::RandBetween(0, 100) < propabilityInPercents) {
			auto first_idx = randomutils::RandBetween(0, path_size - 1);
			auto sec_idx = randomutils::RandBetween(0, path_size - 1);
			// jeśli drugi zostałby wylosowany tym samym
			while (first_idx == sec_idx)
				sec_idx = randomutils::RandBetween(0, path_size - 1);

//			cout << "#mutate#" << " first_idx: " << first_idx << " second_idx: " << sec_idx << endl;

			new_individual->swap_path(first_idx, sec_idx);
		}
	}
	if (this == new_individual.get()) {
		// none bits mutated, so no new individual has been created
		return none;
	}

	return optional<shared_ptr<Individual>>(new_individual);
}

void Individual::resetPath() {
//	#pragma omp parallel for
	for (uint i = 0; i < path.size(); i++) {
		path[i] = City();
	}
}

int main_() {
	shared_ptr<Map> map = shared_ptr<Map>(
			Map::ReadMapFromFile("conf/mapa.txt"));
	map->print();
	Individual i1(map);
	cout << "///////////////////////////" << endl;
	Individual i2(map);
	cout << endl;
	cout << "IND1 " << i1 << endl;
	cout << "IND2 " << i2 << endl;

	auto pr = i1.RandomlyCrossover(1, i2);
	cout << endl << "child 1: " << pr.get().first << endl;
	cout << endl << "child 2: " << pr.get().second << endl;

//	cout << endl << "binary repr 2: " << mutant.get().get()->first.GetBinaryReprezentation() << endl;
	auto mutant = i1.RandomlyMutate(0.5);
	cout << endl << "parent: " << i1 << endl;
	cout << endl << "mutant: " << *(mutant.get()) << endl;

	return 0;
}
