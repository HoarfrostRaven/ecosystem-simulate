#include <cmath>
#include <iostream>
#include <vector>
#include <string>

#include "Fearful.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

using namespace std;

Fearful::Fearful(Milieu* milieu, string name) {
    this->milieu=milieu;
    this->name = name;
}

Fearful::~Fearful() {}

void Fearful::updateParameters(Bug *bug) {
    vector<Bug *> neighbors = milieu->getNeighbors(bug);
    int num_neighbor = neighbors.size();
    
    if (num_neighbor > 0) {
        double avg_orientation = 0;
        
        // Obtain the average of the relative directions of neighbouring bugs to this bug
        for (auto neighbor : neighbors) {
            double neighbor_orientation = atan2(neighbor->getY() - bug->getY(), neighbor->getX() - bug->getX());
            while (neighbor_orientation < 0) {
                neighbor_orientation += 2 * M_PI;
            }
            while (neighbor_orientation >= 2 * M_PI) {
                neighbor_orientation -= 2 * M_PI;
            }
            avg_orientation += neighbor_orientation;
        }
        avg_orientation /= num_neighbor;
        
        // Setting a new direction with a slight yaw
        auto factor = Random::get(0.2, 1.0);
        double new_orientation = avg_orientation + M_PI * factor;
        
        while (new_orientation < 0) {
            new_orientation += 2 * M_PI;
        }
        while (new_orientation >= 2 * M_PI) {
            new_orientation -= 2 * M_PI;
        }
        
        bug->setOrientation(new_orientation);
    }
    
    // Accelerate when the number of neighboring bugs is greater than a certain value
    if (num_neighbor > 2) {
        bug->switchToFastVelocity();
    } else {
        bug->switchToNormalVelocity();
    }
}

Behavior* Fearful::clone() {
    Fearful* behavior = this;
    return dynamic_cast<Behavior *>(behavior);
}
