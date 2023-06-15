#include <map>
#include <string>
#include "BehaviorFactory.h"
#include "../environment/Milieu.h"
#include "Behavior.h"
#include "Careful.h"
#include "Fearful.h"
#include "Social.h"
#include "MultiPersona.h"
#include "SuicideBoomer.h"

using namespace std;

BehaviorFactory* BehaviorFactory::factory = nullptr;
const string BehaviorFactory::carefull = "Carefull";
const string BehaviorFactory::fearful = "Fearful";
const string BehaviorFactory::multipersona = "MultiPersona";
const string BehaviorFactory::social = "Social";
const string BehaviorFactory::suicideboomer = "SuicideBoomer";


BehaviorFactory::BehaviorFactory(Milieu* milieu) {
    this->milieu = milieu;
    behaviors[carefull] = new Careful(milieu, carefull);
    behaviors[fearful] = new Fearful(milieu, fearful);
    behaviors[social] = new Social(milieu, social);
    behaviors[suicideboomer] = new SuicideBoomer(milieu, suicideboomer);
}

BehaviorFactory* BehaviorFactory::getBehaviorFactory(Milieu *milieu) {
    if(factory == nullptr) {
        factory = new BehaviorFactory(milieu);
    }
    return factory;
}

Behavior* BehaviorFactory::getCareful() {
    return behaviors[carefull];
}

Behavior* BehaviorFactory::getFearful() {
    return behaviors[fearful];
}

// Each bug with multiple personalities will have different personalities at the same time
// therefore cannot use flyweight
Behavior* BehaviorFactory::getMultiPersona() {
    return dynamic_cast<Behavior *>(new MultiPersona(milieu, multipersona, behaviors));
}

Behavior* BehaviorFactory::getSocial() {
    return behaviors[social];
}

Behavior* BehaviorFactory::getSuicideBoomer() {
    return behaviors[suicideboomer];
}

BehaviorFactory::~BehaviorFactory() {
    for (auto entry : behaviors) {
        delete entry.second;
    }

    factory = nullptr;
    behaviors.clear();
}
