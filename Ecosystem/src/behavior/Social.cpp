//
// Created by Franck XU on 16/03/2023.
//

#include "Social.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

Social::Social(Milieu* milieu, string name) {
    this->milieu = milieu;
    this->name = name;
}

Social::~Social() {}

void Social::updateParameters(Bug *bug) {
    vector<Bug *> const neighbors = milieu->getNeighbors(bug);
    
    if (neighbors.size() > 0) {
        double orientation = 0;
        
        // Get the average orientation of neighbouring bugs
        for (auto neighbor : neighbors) {
            orientation += neighbor->getOrientation();
        }
        
        orientation /= neighbors.size();
        
        while(orientation < 0) {
            orientation += 2 * M_PI;
        }

        while(orientation >= 2 * M_PI) {
            orientation -= 2 * M_PI;
        }
        
        bug->setOrientation(orientation);
    }
    
}

Behavior* Social::clone() {
    Social* behavior = this;
    return dynamic_cast<Behavior *>(behavior);
}
