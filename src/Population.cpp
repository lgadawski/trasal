#include "Population.h"

using namespace std;
using namespace boost;

Population::Population(const shared_ptr<Map> amap, const int apopSize) :
		map(amap),
		populationSize(apopSize) {
	for (int var = 0; var < populationSize; ++var) {
		Individual *i = new Individual(map);
		cout << endl << " d1 " << endl;
		individuals.insert(*i);
		cout << endl << " d2 " << endl;
	}
	cout << " pop created ";
}

void Population::RandomlyCrossover(const double crossoverPropability) {
	// TODO po
	//dobieranie w pary
	std::vector<Individual> vIndividuals(individuals.size());
	std::copy(individuals.begin(), individuals.end(), vIndividuals.begin());
	std::vector<pair<Individual, Individual>> pairs;
	while(vIndividuals.size()>0){//dopoki niewszystkie elementy dobrane są w pary
		// losuje indeksy elementów do połączenia
		int index1 = randomutils::RandBetween(0,vIndividuals.size());
		int index2 = randomutils::RandBetween(0,vIndividuals.size());
		std::vector<Individual>::iterator it1 = std::next(vIndividuals.begin(),index1);
		std::vector<Individual>::iterator it2 = std::next(vIndividuals.begin(),index2);

		//tworze z nich pare
		pair<Individual, Individual> pi(vIndividuals[index1], vIndividuals[index2]);
		pairs.push_back(pi);

		//usuwam z pomocniczego wektora , żeby uniknąć dupplikacji
		vIndividuals.erase(it1);
		vIndividuals.erase(it1);
	}

	for(vector<pair<Individual,Individual>>::iterator it = pairs.begin() ; it != pairs.end() ; it++){
		it->first.RandomlyCrossover(crossoverPropability, it->second);
	}

}

void Population::RandomlyMutate(const double mutatePropability) {
	for (set<Individual>::iterator it = individuals.begin(); it != individuals.end(); ++it) {
		optional<shared_ptr<Individual>> opt = it->RandomlyMutate(mutatePropability);
		if (opt) {
			mutatedIndividuals.insert(*(opt.get().get()));
		}
	}
}

Individual Population::GetBestIndividual() {
	// first element in set has lowest value due to overloaded < operator
	return (*(individuals.begin()));
}
