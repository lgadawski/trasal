#include "Population.h"
#include <map>

using namespace std;
using namespace boost;

Population::Population(const shared_ptr<Map> amap, const int apopSize) :
		map(amap),
		population_size(apopSize) {
	for (int var = 0; var < population_size; ++var) {
		Individual *i = new Individual(map);
		individuals.push_back(*i);
	}

	sort(individuals.begin(), individuals.end());
	print_summary();
}

Population::Population(const std::vector<Individual> aindividuals, const std::shared_ptr<Map> amap, const int apopulation_size) :
		individuals(aindividuals),
		map(amap),
		population_size(apopulation_size) {
	sort(individuals.begin(), individuals.end());
	print_summary();
}

void Population::print_summary() {
	cout << endl << "POPULATION CREATED, LENS: ";
	for (auto &&x : individuals) cout << endl << x.GetLength() << " PROPAB: " << x.GetPropability();
	cout << endl << "FINISH ------------------" << endl;
}

void Population::RandomlyCrossover(const double crossoverPropability) {
	//dobieranie w pary
	std::vector<Individual> vIndividuals(individuals.size());
	std::copy(individuals.begin(), individuals.end(), vIndividuals.begin());
	std::vector<pair<Individual, Individual>> pairs;
	while (vIndividuals.size()>0) {//dopoki niewszystkie elementy dobrane są w pary
		// losuje indeksy elementów do połączenia
		int index1 = randomutils::RandBetween(0, vIndividuals.size());
		int index2 = randomutils::RandBetween(0, vIndividuals.size());
		std::vector<Individual>::iterator it1 = std::next(vIndividuals.begin(), index1);
		std::vector<Individual>::iterator it2 = std::next(vIndividuals.begin(), index2);

		//tworze z nich pare
		pairs.push_back(pair<Individual, Individual>(vIndividuals[index1], vIndividuals[index2]));

		//usuwam z pomocniczego wektora , żeby uniknąć dupplikacji
		vIndividuals.erase(it1);
		vIndividuals.erase(it2);
	}

	for (vector<pair<Individual,Individual>>::iterator it = pairs.begin() ; it != pairs.end() ; it++) {
		it->first.RandomlyCrossover(crossoverPropability, it->second);
	}

}

void Population::RandomlyMutate(const double mutatePropability) {
	for (vector<Individual>::iterator it = individuals.begin(); it != individuals.end(); ++it) {
		optional<shared_ptr<Individual>> opt = it->RandomlyMutate(mutatePropability);
		if (opt) {
			mutatedIndividuals.push_back(*(opt.get().get()));
		}
	}
}

Individual Population::GetBestIndividual() {
	// first element in set has lowest value due to overloaded < operator
	return (*(individuals.begin()));
}

int Population::GetAdaptationSumLen() const {
	auto result = 0;
	for (auto &&ind : individuals) {
		result += ind.GetLength();
	}

	return result;
}

int Population::GetPropabDivision(int sum) const {
	auto result = 0;
	for (auto &&ind : individuals) {
		result += (sum - ind.GetLength());
	}

	return result;
}

Individual Population::GetIndividualBySeq(int seq) const {
	for (auto &&ind : individuals) {
		if (ind.GetSeq() == seq) {
			return ind;
		}
	}

	throw runtime_error("Population::GetIndividualBySeq");
}

shared_ptr<Population> Population::Reproduce() {
	cout << endl << "START reproduce" << endl;
	int i = 0, sum = GetAdaptationSumLen();
	double cumulative_distribution = 0.0;
	// sum_sum_x_i, where: propab = (len_sum - x) / (sum(len_sum - x_i))
	int sum_sum_x_i = GetPropabDivision(sum);

	std::map<int, pair<double, double>> ind_seq_to_cumulative_range;
	for (vector<Individual>::iterator it = individuals.begin(); it != individuals.end(); ++it) {
		it->CalculatePropability(sum, sum_sum_x_i);
		it->SetSeq(i++);
		cumulative_distribution += it->GetPropability();
		it->SetCumulativeDistribution(cumulative_distribution);
		ind_seq_to_cumulative_range[it->GetSeq()] =
				pair<double, double>(cumulative_distribution - it->GetPropability(), cumulative_distribution);
	}

	cout << endl << "Before random roulette!";
	for (auto &&x : individuals) cout << endl << "len: " << x.GetLength() << " propab: " << x.GetPropability();
	cout << endl << "End of roulette!" << endl;

	vector<Individual> new_set;
	for (int it = 0; it < population_size; ++it) {
		double random_a = ((double) randomutils::RandBetween(0, 100)) * 0.01; // z przedzialu (0, 1)

		cout << endl << endl << "RANDOM_A: " << random_a;

		for (auto &&ind_pair : ind_seq_to_cumulative_range) {
			cout << endl << "[" << ind_pair.second.first << ", " << ind_pair.second.second << "]";

			if (random_a <= ind_pair.second.second && random_a >= ind_pair.second.first) {
				new_set.push_back(GetIndividualBySeq(ind_pair.first));
			}
		}
	}
	shared_ptr<Population> result(new Population(new_set, map, population_size));

	return result;
}
