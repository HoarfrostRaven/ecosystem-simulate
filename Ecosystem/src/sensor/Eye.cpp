#include <cmath>
#include "Eye.h"
#include "../bug/Bug.h"
#include "../../include/Random.h"
#include "../../include/HMI/UImg.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

double Eye::ANGLE_MIN = 0.2 * M_PI;
double Eye::ANGLE_MAX = 0.8 * M_PI;
double Eye::DISTANCE_MIN = 40.;
double Eye::DISTANCE_MAX = 80.;
double Eye::DETECT_CAPACITY_MIN = 20.;
double Eye::DETECT_CAPACITY_MAX = 100.;

Eye::Eye(Bug* owner) {
    this->owner = owner;
    this->detectCapacity = Random::get(Eye::DETECT_CAPACITY_MIN, Eye::DETECT_CAPACITY_MAX);
    this->distance = Random::get(Eye::DISTANCE_MIN, Eye::DISTANCE_MAX);
    this->angle = Random::get(Eye::ANGLE_MIN, Eye::ANGLE_MAX);
}

Eye::Eye(Bug* owner, double detectCapacity, double distance, double angle) {
    this->owner = owner;
    this->detectCapacity = detectCapacity;
    this->distance = distance;
    this->angle = angle;
}

Sensor* Eye::clone(Bug* owner) const {
    return dynamic_cast<Sensor *>(new Eye(owner, this->detectCapacity, this->distance, this->angle));
}

void Eye::draw(UImg &support) const {
    T* color = new T[3];
    color[0] = 200;
    color[1] = 200;
    color[2] = 200;
    
    double orientation = this->owner->getOrientation(); // rad
    int x = this->owner->getX();
    int y = this->owner->getY();
    
    // The origin is in the upper left corner
    // x-axis goes right
    // y-axis goes down
    // counter-clockwise
    double x1 = x + std::cos(orientation)*Bug::SIZE/2.1;
    double y1 = y - std::sin(orientation)*Bug::SIZE/2.1;
    
    double x2 = x1 + std::cos(orientation + this->angle / 2) * this->distance;
    double y2 = y1 - std::sin(orientation + this->angle / 2) * this->distance;
    
    double x3 = x1 + std::cos(orientation - this->angle / 2) * this->distance;
    double y3 = y1 - std::sin(orientation - this->angle / 2) * this->distance;
    
    support.draw_triangle(x1, y1, x2, y2, x3, y3, color, 0.2);
}

bool Eye::isDetected(Bug* bug) const {
    if (this->detectCapacity <= bug->getCamouflageCapacity()) {
        return false;
    }
    
    int x1 = this->owner->getX();
    int y1 = this->owner->getY();
    
    int x2 = bug->getX();
    int y2 = bug->getY();
    
    double myDistance = std::sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
    if (myDistance >= this->distance) {
        return false;
    }
    
    double orientation = this->owner->getOrientation(); // rad
    double myAngle = std::atan2(x1-x2, y1-y2);
    if (abs(orientation - myAngle) >= this->angle/2) {
        return false;
    }
    
    return true;
}
