#include "Fin.h"
#include "../bug/Bug.h"
#include "../../include/Random.h"

double Fin::FACTOR_VELOCITY = 1.2;

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

void Fin::updateParameters(Bug* bug) const {
    double randomFactor = Random::get(1., Fin::FACTOR_VELOCITY);
    bug->updateVelocity(randomFactor);
}
