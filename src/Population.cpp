#include "Population.h"

using namespace std;
using namespace boost;

Population::Population(shared_ptr<Map> amap, int apopSize) :
		map(amap),
		populationSize(apopSize) {
	// FIXME

}

void Population::RandomlyCrossover(const double crossoverPropability) {
	// FIXME
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
	// FIXME
//	return bestIndividual
}

