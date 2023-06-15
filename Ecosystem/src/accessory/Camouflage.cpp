#include "Camouflage.h"
#include "../bug/Bug.h"
#include "../../include/Random.h"

double Camouflage::FACTOR_CAMOUFLAGE_MIN = 0.1;
double Camouflage::FACTOR_CAMOUFLAGE_MAX = 0.9;

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

void Camouflage::updateParameters(Bug* bug) const {
    double randomFactor = Random::get(Camouflage::FACTOR_CAMOUFLAGE_MIN, Camouflage::FACTOR_CAMOUFLAGE_MAX);
    bug->updateCamouflageCapacity(randomFactor);
}
