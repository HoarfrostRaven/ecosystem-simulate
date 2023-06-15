#include "Careful.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;
using namespace std;

Careful::Careful(Milieu* milieu, string name) {
    this->milieu = milieu;
    this->name = name;
}

Careful::~Careful() {}

void Careful::updateParameters(Bug *bug) {
    auto bug_velocity = bug->getCurrentVelocity();
    auto bug_orientation = bug->getOrientation();
    auto bug_x_esti = bug->getX() + bug_velocity * cos(bug_orientation);
    auto bug_y_esti = bug->getY() - bug_velocity * sin(bug_orientation);

    Bug const* closest_neighbor = nullptr;
    double closest_distance = std::numeric_limits<double>::infinity();

    vector<Bug *> const neighbors = milieu->getNeighbors(bug);
    for (auto neighbor : neighbors) {
        auto velocity = neighbor->getCurrentVelocity();
        auto orientation = neighbor->getOrientation();

        auto neighbor_x_esti = neighbor->getX() + velocity * cos(orientation) ;
        auto neighbor_y_esti = neighbor->getY() - velocity * sin(orientation);

        // Estimating the distance between insects and the risk of imminent collision
        double diff_distance = pow(neighbor_x_esti - bug_x_esti, 2) + pow(neighbor_y_esti - bug_y_esti, 2);

        if (diff_distance < closest_distance) {
            closest_distance = diff_distance;
            closest_neighbor = neighbor;
        }
    }

    if (closest_neighbor) {
        // Collision avoidance and reorientation
        double neighbor_orientation = closest_neighbor->getOrientation();
        double delta_orientation = neighbor_orientation - bug_orientation;
        auto factor = Random::get(0.2, 0.5);
        double perpendicular_orientation = delta_orientation + M_PI * factor;
        bug->setOrientation(perpendicular_orientation);
    }
}

Behavior* Careful::clone() {
    Careful* behavior = this;
    return dynamic_cast<Behavior *>(behavior);
}
