#include "Population.h"
#include <omp.h>
#include <map>

using namespace std;
using namespace boost;

Population::Population(const shared_ptr<Map> amap, const int apopSize) :
		map(amap), population_size(apopSize) {

	individuals.resize(population_size);
	#pragma omp parallel for
	for (int var = 0; var < population_size; ++var) {
		Individual *i = new Individual(map);
		individuals[var] = *i;
	}

	sort(individuals.begin(), individuals.end());
//	print_summary();
}

Population::Population(const std::vector<Individual> aindividuals,
		const std::shared_ptr<Map> amap, const int apopulation_size) :
		individuals(aindividuals), map(amap), population_size(apopulation_size) {
	sort(individuals.begin(), individuals.end());
//	print_summary();
}

void Population::print_summary() {
	cout << endl << "POPULATION CREATED, LENS: ";
	for (auto &&x : individuals)
		cout << endl << x.GetLength() << " PROPAB: " << x.GetPropability();
	cout << endl << "FINISH ------------------" << endl;
}

void Population::RandomlyCrossover(const double crossoverPropability) {
	//dobieranie w pary
	vector<Individual> vIndividuals(individuals.size());
	copy(individuals.begin(), individuals.end(), vIndividuals.begin());

	vector<pair<Individual, Individual>> pairs;
	//dopoki nie wszystkie elementy dobrane są w pary
	while (!vIndividuals.empty()) {
		// losuje indeksy elementów do połączenia
		int index1 = randomutils::RandBetween(0, vIndividuals.size() - 1);
		int index2 = randomutils::RandBetween(0, vIndividuals.size() - 1);
//		cout << endl << "idx1: " << index1 << " idx2: " << index2 << " ind size: " << vIndividuals.size();
		if (index1 != index2) {
			//tworze z nich pare
			pairs.push_back(
					pair<Individual, Individual>(vIndividuals[index1], vIndividuals[index2]));

			auto it1 = std::next(vIndividuals.begin(), index1);
			auto it2 = std::next(vIndividuals.begin(), index2);

			//usuwam z pomocniczego wektora, żeby uniknąć duplikacji
			vIndividuals.erase(it1);
			vIndividuals.erase(it2);
		}
		if (vIndividuals.size() == 1 && index1 == 0 && index2 == 0) {
			break;
		}
	}
	individuals.clear();

	individuals.resize(pairs.size());
//	#pragma omp parallel for
	for (int i = 0; i < pairs.size(); ++i) {
		auto opt = pairs[i].first.RandomlyCrossover(crossoverPropability, pairs[i].second);
		if (opt) {
			individuals[i] = opt.get().first;
			individuals[i] = opt.get().second;
		} else {
			individuals[i] = pairs[i].first;
			individuals[i] = pairs[i].second;
		}
	}

	if (vIndividuals.size() == 1) {
		// add orphan
		individuals.push_back(vIndividuals[0]);
	}
	sort(individuals.begin(), individuals.end());
}

void Population::RandomlyMutate(const double mutatePropability) {
	std::vector<Individual> result(individuals.size());
	std::copy(individuals.begin(), individuals.end(), result.begin());
	individuals.clear();

	individuals.resize(result.size());
	#pragma omp parallel for
	for (int i = 0; i < result.size(); ++i) {
		auto opt = result[i].RandomlyMutate(mutatePropability);
		if (opt) {
			individuals[i] = *(opt.get());
		} else {
			individuals[i] = result[i];
		}
	}

	sort(individuals.begin(), individuals.end());
}

Individual Population::GetBestIndividual() {
	// first element in set has lowest value due to overloaded < operator
	return (*(individuals.begin()));
}

int Population::GetAdaptationSumLen() const {
	auto result = 0;

	#pragma omp parallel
	{
		#pragma omp for reduction(+:result)
		for (int i = 0; i < individuals.size(); ++i) {
			result += individuals[i].GetLength();
		}
	}

	return result;
}

int Population::GetPropabDivision(int sum) const {
	auto result = 0;

	#pragma omp parallel shared(sum)
	{
		#pragma omp for reduction(+:result)
		for (int i = 0; i < individuals.size(); ++i) {
			result += (sum - individuals[i].GetLength());
		}
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
	int sum = GetAdaptationSumLen();
	double cumulative_distribution = 0.0;
	// sum_sum_x_i, where: propab = (len_sum - x) / (sum(len_sum - x_i))
	int sum_sum_x_i = GetPropabDivision(sum);

	std::map<int, pair<double, double>> ind_seq_to_cumulative_range;

	for (int c = 0; c < individuals.size(); ++c) {
		individuals[c].CalculatePropability(sum, sum_sum_x_i);
		individuals[c].SetSeq(c);
		cumulative_distribution += individuals[c].GetPropability();
		individuals[c].SetCumulativeDistribution(cumulative_distribution);
		ind_seq_to_cumulative_range[individuals[c].GetSeq()] = pair<double, double>(
				cumulative_distribution - individuals[c].GetPropability(),
				cumulative_distribution);
	}

//	cout << endl << "Before random roulette!";
//	for (auto &&x : individuals)
//		cout << endl << "len: " << x.GetLength() << " propab: " << x.GetPropability();
//	cout << endl << "End of roulette!" << endl;

	vector<Individual> new_set;
	for (int it = 0; it < population_size; ++it) {
		double random_a = ((double) randomutils::RandBetween(0, 100)) * 0.01;
//		cout << endl << endl << "RANDOM_A: " << random_a;

		for (auto &&ind_pair : ind_seq_to_cumulative_range) {
//			cout << endl << "[" << ind_pair.second.first << ", " << ind_pair.second.second << "]";
			if (random_a <= ind_pair.second.second && random_a >= ind_pair.second.first) {
				new_set.push_back(GetIndividualBySeq(ind_pair.first));
				break;
			}
		}
	}
	shared_ptr<Population> result(new Population(new_set, map, population_size));

	return result;
}
