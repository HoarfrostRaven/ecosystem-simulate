//
// Created by Franck XU on 16/03/2023.
//

#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

#include "SuicideBoomer.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include "UImg.h"
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;
using namespace std;

SuicideBoomer::SuicideBoomer(Milieu* milieu, string name) {
    this->milieu=milieu;
    this->name = name;
}

SuicideBoomer::~SuicideBoomer() {}

void SuicideBoomer::updateParameters(Bug *bug) {
    auto bug_x = bug->getX();
    auto bug_y = bug->getY();

    int closest_neighbor_x;
    int closest_neighbor_y;
    double closest_distance = std::numeric_limits<double>::infinity();

    vector<Bug *> const neighbors = milieu->getNeighbors(bug);
    for (auto neighbor : neighbors) {
        auto neighbor_x = neighbor->getX();
        auto neighbor_y = neighbor->getY();

        // Find the nearest bug
        double diff_distance = pow(neighbor_x - bug_x, 2) + pow(neighbor_y - bug_y, 2);

        if (diff_distance < closest_distance) {
            closest_distance = diff_distance;
            closest_neighbor_x = neighbor_x;
            closest_neighbor_y = neighbor_y;
        }
    }

    // When a target appears, bug has a 0.8 probability of chasing the target
    // This probability will prevent boomers from getting stuck together
    if (closest_distance < std::numeric_limits<double>::infinity() && Random::get<bool>(0.8)) {
        double orientation = atan2(bug_y - closest_neighbor_y, bug_x - closest_neighbor_x);
        
        while (orientation < 0) {
            orientation += 2 * M_PI;
        }
        while (orientation >= 2 * M_PI) {
            orientation -= 2 * M_PI;
        }
        
        bug->setOrientation(orientation);
    }
}

Behavior* SuicideBoomer::clone() {
    SuicideBoomer* behavior = this;
    return dynamic_cast<Behavior *>(behavior);
}
