#include "MultiPersona.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include "Behavior.h"
#include <vector>
#include <map>
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

MultiPersona::MultiPersona(Milieu* milieu, string name, std::map<string, Behavior*> &behaviors) {
    this->milieu=milieu;
    this->name = name;
    for (auto b : behaviors) {
        this->behaviors.push_back(b.second);
    }
    this->numBehavior = this->behaviors.size() - 1;
    updateBehavior();
}

MultiPersona::MultiPersona(const MultiPersona& multiPersona) {
    this->behaviors = multiPersona.behaviors;
    this->numBehavior = multiPersona.numBehavior;
    this->milieu = multiPersona.milieu;
    this->name = multiPersona.name;
    updateBehavior();
}

MultiPersona::~MultiPersona() {
}

// Will randomly transfer to a new personality at random intervals
void MultiPersona::updateBehavior() {
    time = Random::get(30, 300);
    int random_number = Random::get(0, numBehavior);
    currentBehavior = behaviors[random_number];
}

void MultiPersona::updateParameters(Bug* bug) {
    if(time == 0) {
        updateBehavior();
    } else {
        time--;
    }
    
    this->currentBehavior->updateParameters(bug);
}

Behavior* MultiPersona::clone() {
    return dynamic_cast<Behavior *>(new MultiPersona(*this));
}
