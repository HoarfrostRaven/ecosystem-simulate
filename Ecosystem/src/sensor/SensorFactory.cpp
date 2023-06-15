#include "SensorFactory.h"
#include "Ear.h"
#include "Eye.h"
#include "../bug/Bug.h"

SensorFactory* SensorFactory::factory = nullptr;

SensorFactory::SensorFactory(){}

SensorFactory::~SensorFactory() {
    factory = nullptr;
}

SensorFactory* SensorFactory::getSensorFactory() {
    if(factory == nullptr) {
        factory = new SensorFactory();
    }
    return factory;
}

void SensorFactory::attachEye(Bug* bug) const {
    Eye* eye = new Eye(bug);
    bug->addSensor(eye);
}

void SensorFactory::attachEar(Bug* bug) const {
    Ear* ear = new Ear(bug);
    bug->addSensor(ear);
}

void SensorFactory::attachSensors(Bug* bug) const {
    attachEye(bug);
    attachEar(bug);
}
