#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Milieu.h"
#include "../bug/Bug.h"
#include <stdexcept>

const T Milieu::white[] = {(T)255, (T)255, (T)255};
int Milieu::NUM_BUG = 0;
int Milieu::NUM_COLLISION = 0;
int Milieu::NUM_CLONE = 0;
int Milieu::NUM_DEATH_BY_COLLISION = 0;
int Milieu::NUM_DEATH_BY_KILL = 0;
int Milieu::NUM_DEATH_BY_AGE = 0;
int Milieu::NUM_CAREFUL = 0;
int Milieu::NUM_FEARFUL = 0;
int Milieu::NUM_MULTI_PERSONA = 0;
int Milieu::NUM_SOCIAL = 0;
int Milieu::NUM_SUCIDE_BOOMER = 0;

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3), width(_width), height(_height) {
    cout << "const Milieu" << endl;
    std::srand(time(NULL));
}

Milieu::~Milieu() {
    cout << "Destruct the Milieu" << endl;
}

void Milieu::step() {
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);
    
    // delete and erase dead bugs
    listBugs.erase(std::remove_if(listBugs.begin(), listBugs.end(), [](Bug* b){
        bool isDead = !b->isAlive();
        if(isDead) delete b;
        return isDead;
    }), listBugs.end());

    // draw and act living bugs
    int size = listBugs.size();
    for (int i = 0; i < size; ++i) {
        listBugs[i]->draw(*this);
        listBugs[i]->action();
    }
    
    // show current analyse result
    showAnalyseResult();
}

void Milieu::addBug(Bug* bug) {
    Milieu::NUM_BUG++;
    listBugs.push_back(bug);
    listBugs.back()->initLocation(getWidth(), getHeight());
}

void Milieu::removeBug(Bug* bug) {
    auto it = std::find(listBugs.begin(), listBugs.end(), bug);

    if (it != listBugs.end()) {
        listBugs.erase(it);
    }
}

int Milieu::getNumNeighbors(Bug* bug) {
    int nb = 0;
    
    for (std::vector<Bug*>::iterator it = listBugs.begin(); it != listBugs.end(); ++it)
        if (!(bug == *it) && (*it)->isAlive() && bug->isDetected(*it)) {
            ++nb;
        }

    return nb;
}

std::vector<Bug*> Milieu::getNeighbors(Bug* bug) {
    std::vector<Bug*> neighbors;

    for (std::vector<Bug*>::iterator it = listBugs.begin(); it != listBugs.end(); ++it) {
        if (!(bug == *it) && (*it)->isAlive() && bug->isDetected(*it)) {
            neighbors.push_back(*it);
        }
    }

    return neighbors;
}

std::vector<Bug*> Milieu::getBugs() {
    return listBugs;
}

void Milieu::kill() {
    for (std::vector<Bug*>::iterator it = listBugs.begin(); it != listBugs.end(); ++it){
        if ((*it)->isAlive()) {
            Milieu::NUM_DEATH_BY_KILL++;
            (*it)->kill();
            return;
        }
    }
}

void Milieu::showAnalyseResult() {
    Color color = {0, 0, 0};
    
    std::string numBug = "Number of bug : " + to_string(NUM_BUG);
    std::string numDeath = "Number of death : " + to_string(NUM_DEATH_BY_COLLISION+NUM_DEATH_BY_KILL+NUM_DEATH_BY_AGE);
    std::string numCollision = "Number of collision : " + to_string(NUM_COLLISION);
    std::string numClone = "Number of clone : " + to_string(NUM_CLONE);
    std::string numCareful = "Number of careful : " + to_string(NUM_CAREFUL);
    std::string numFearful = "Number of fearful : " + to_string(NUM_FEARFUL);
    std::string numMultiPersona = "Number of multi persona : " + to_string(NUM_MULTI_PERSONA);
    std::string numSocial = "Number of social : " + to_string(NUM_SOCIAL);
    std::string numSucideBoomer = "Number of sucide boomer : " + to_string(NUM_SUCIDE_BOOMER);
    
    draw_text(0, MILIEU_HEIGHT+30, numBug.c_str() , color.data(),0,1,24);
    draw_text(0, MILIEU_HEIGHT+60, numMultiPersona.c_str() , color.data(),0,1,24);
    draw_text(0, MILIEU_HEIGHT+90, numFearful.c_str() , color.data(),0,1,24);
    draw_text(0, MILIEU_HEIGHT+120, numSucideBoomer.c_str() , color.data(),0,1,24);
    draw_text(0, MILIEU_HEIGHT+150, numSocial.c_str() , color.data(),0,1,24);
    draw_text(0, MILIEU_HEIGHT+180, numCareful.c_str() , color.data(),0,1,24);
    
    draw_text(350, MILIEU_HEIGHT+30, numDeath.c_str() , color.data(),0,1,24);
    draw_text(350, MILIEU_HEIGHT+60, numCollision.c_str() , color.data(),0,1,24);
    draw_text(350, MILIEU_HEIGHT+90, numClone.c_str() , color.data(),0,1,24);
}

void Milieu::resetAnalyseResult() {
    Milieu::NUM_BUG = 0;
    Milieu::NUM_COLLISION = 0;
    Milieu::NUM_CLONE = 0;
    Milieu::NUM_DEATH_BY_COLLISION = 0;
    Milieu::NUM_DEATH_BY_KILL = 0;
    Milieu::NUM_DEATH_BY_AGE = 0;
    Milieu::NUM_CAREFUL = 0;
    Milieu::NUM_FEARFUL = 0;
    Milieu::NUM_MULTI_PERSONA = 0;
    Milieu::NUM_SOCIAL = 0;
    Milieu::NUM_SUCIDE_BOOMER = 0;
}
