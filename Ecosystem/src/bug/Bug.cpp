#include "Bug.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <string>

#include "../sensor/Sensor.h"
#include "../behavior/Behavior.h"
#include "../environment/Milieu.h"
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;
using namespace std;

const double Bug::MAX_AGE = 1000;
const double Bug::MIN_AGE = 100;
const double Bug::MAX_SIGHT = 30.0;
const double Bug::MIN_SIGHT = 10.0;
const double Bug::SIZE = 8.0;
const double Bug::MAX_VELOCITY = 3.0;
const double Bug::MIN_VELOCITY = 2.0;
const double Bug::MAX_CLONE_PROB = 0.001;
const double Bug::MAX_DEATH_PROB = 0.05;
const double Bug::MIN_DEATH_PROB = 0.01;
int Bug::NUM_BUGS = 0;

Bug::Bug(Milieu* milieu) {
    // Initialization
    this->milieu = milieu;
    this->ID = ++NUM_BUGS;

    x = y = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>(rand())/RAND_MAX*2.*M_PI;

    this->normalVelocity = Random::get(MIN_VELOCITY, MAX_VELOCITY * 0.8);
    this->fastVelocity = Random::get(Bug::MAX_VELOCITY * 0.8, Bug::MAX_VELOCITY);
    this->currentVelocity = normalVelocity;

    this->age = 0;
    this->ageLimit = Random::get(Bug::MIN_AGE, Bug::MAX_AGE);
    this-> alive = true;

    this->camouflageCapacity = 0;
    this->cloneProbability = Random::get(0., Bug::MAX_CLONE_PROB);
    this->deathProbability = Random::get(Bug::MIN_DEATH_PROB, Bug::MAX_DEATH_PROB);

    this->behavior = nullptr;
}

// copy function
Bug::Bug(const Bug& bug) {
    this->ID = ++NUM_BUGS;
    this->milieu = bug.milieu;
    
    x = bug.x;
    y = bug.y;
    orientation = bug.orientation;
    cumulX = cumulY = 0.;

    this->normalVelocity = bug.normalVelocity;
    this->currentVelocity = bug.currentVelocity;
    this->fastVelocity = bug.fastVelocity;

    // other variables
    this->age = 0;
    this->ageLimit = bug.ageLimit;
    this->alive = true;

    this->camouflageCapacity = bug.camouflageCapacity;
    this->cloneProbability = bug.cloneProbability;
    this->deathProbability = bug.deathProbability;

    sensors.clear();
    for (auto const &sensor : bug.sensors) {
        sensors.push_back(sensor->clone(this));
    } // clone all the capteurs

    if (bug.behavior) {
        this->behavior = bug.behavior->clone();
    } // set the behavior
}

Bug::~Bug() {
    for (auto sensor : sensors) {
        delete sensor;
    }
}

void Bug::action() {
    // Natural death
    age++;
    if (age > ageLimit) {
        Milieu::NUM_DEATH_BY_AGE++;
        kill();
        return;
    }

    // Get all bugs and detect if this bug has collided with them
    const auto bugs = milieu->getBugs();
    
    for (auto bug : bugs) {
        if(bug->isAlive() && !(bug == this)) {
            if (this->isCollidingWith(bug)) {
                Milieu::NUM_COLLISION++;
                if (Random::get<bool>(deathProbability)) {
                    Milieu::NUM_DEATH_BY_COLLISION++;
                    kill();
                    return;
                }
                auto factor = Random::get(0.2, 1.0);
                this->orientation = orientation + M_PI * factor;
            }
        }
    }

    // Change the speed and direction of the bug according to its personality
    if (behavior) {
        behavior->updateParameters(this);
    }
    
    // There is a certain probability of cloning
    clone();

    // Bugs are in constant motion
    move();
}

void Bug::draw(UImg &support) {
    // Get head coordinates
    double xt = x + cos(orientation) * SIZE / 2.1;
    double yt = y - sin(orientation) * SIZE / 2.1;

    for (auto sensor : sensors) {
        sensor->draw(support);
    }

    auto color = behavior->getColor();

    support.draw_ellipse(x, y, SIZE, SIZE / 5., -orientation / M_PI * 180., color.data());
    support.draw_circle(xt, yt, SIZE / 2., color.data());
}

// Check if this bug detects another bug and return true if the incoming bug has been detected
bool Bug::isDetected(Bug* bug) const {
    for (auto sensor : sensors) {
        if (sensor->isDetected(bug)) {
            return true;
        }
    }
    return false;
}

// Random selection of birthplace
void Bug::initLocation(int xLim, int yLim) {
    this->x = rand() % xLim;
    this->y = rand() % yLim;
}

void Bug::addSensor(Sensor* sensor) {
    this->sensors.push_back(sensor);
}

void Bug::setBehavior(Behavior* behavior) {
    this->behavior = behavior;
}

double Bug::getCamouflageCapacity() const { return camouflageCapacity; }

double Bug::getOrientation() const { return orientation; }

void Bug::switchToFastVelocity() { this->currentVelocity = fastVelocity; }

void Bug::switchToNormalVelocity() { this->currentVelocity = normalVelocity; }

double Bug::getCurrentVelocity() const { return currentVelocity; }

void Bug::setOrientation(double orientation) { this->orientation = orientation; }

// Different accessories (such as fins and shells) will change the speed of the bug
void Bug::updateVelocity(double velocityFactor) {
    normalVelocity = normalVelocity * velocityFactor;
    fastVelocity = fastVelocity * velocityFactor;
    currentVelocity = normalVelocity;
}

void Bug::updateCamouflageCapacity(double camouflageCapacity) {
    this->camouflageCapacity = camouflageCapacity;
}

void Bug::updateDeathProbability(double deathProbFactor) {
    deathProbability = deathProbability * deathProbFactor;
}

bool Bug::isCollidingWith(Bug* bug) const {
    int dx = x - bug->getX();
    int dy = y - bug->getY();
    return dx * dx + dy * dy <= SIZE * SIZE;
}

// Mark the bugs as dead so they can be deleted in the next loop
// if the bugs have multiple personality types, the corresponding behaviouror needs to be deleted
void Bug::kill() {
    alive = false;
    Milieu::NUM_BUG--;
    string behaviorName = this->behavior->getBehaviorName();
    if(behaviorName == "Carefull") {
        Milieu::NUM_CAREFUL--;
    } else if (behaviorName == "Fearful") {
        Milieu::NUM_FEARFUL--;
    } else if (behaviorName == "MultiPersona") {
        delete this->behavior;
        Milieu::NUM_MULTI_PERSONA--;
    } else if (behaviorName == "Social") {
        Milieu::NUM_SOCIAL--;
    } else if (behaviorName == "SuicideBoomer") {
        Milieu::NUM_SUCIDE_BOOMER--;
    }
}

// The bug is always in motion and changes direction of movement randomly
void Bug::move() {
    int xLim = milieu->getWidth();
    int yLim = milieu->getHeight();
    double nx, ny;
    double dx = cos(orientation) * currentVelocity;
    double dy = -sin(orientation) * currentVelocity;
    int cx, cy;

    cx = static_cast<int>(cumulX);
    cumulX -= cx;
    cy = static_cast<int>(cumulY);
    cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;
    
    auto factor_wall = Random::get(0.2, 1.0);
    auto factor_rand = Random::get(-0.05, 0.05);
    orientation += factor_rand * M_PI;

    if ((nx < 0) || (nx > xLim - 1)) { // run into the wall
        orientation = factor_wall * M_PI - orientation;
        cumulX = 0.;
    } else {
        x = static_cast<int>(nx);
        cumulX += nx - x;
    }

     if ((ny < 0) || (ny > yLim - 1)) { // run into the wall
        orientation = orientation + M_PI * factor_wall;
        cumulY = 0.;
    } else {
        y = static_cast<int>(ny);
        cumulY += ny - y;
    }
}

// There is a certain probability of cloning of the bug
void Bug::clone() {
    if (Random::get<bool>(cloneProbability)) {
        Milieu::NUM_CLONE++;
        Bug* bug = new Bug(*this);
        milieu->addBug(bug);
        
        string behaviorName = this->behavior->getBehaviorName();
        if(behaviorName == "Carefull") {
            Milieu::NUM_CAREFUL++;
        } else if (behaviorName == "Fearful") {
            Milieu::NUM_FEARFUL++;
        } else if (behaviorName == "MultiPersona") {
            Milieu::NUM_MULTI_PERSONA++;
        } else if (behaviorName == "Social") {
            Milieu::NUM_SOCIAL++;
        } else if (behaviorName == "SuicideBoomer") {
            Milieu::NUM_SUCIDE_BOOMER++;
        }
    }
}
