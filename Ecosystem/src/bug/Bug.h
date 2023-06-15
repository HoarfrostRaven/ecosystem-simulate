#ifndef _Bug_H_
#define _Bug_H_

#include <vector>
#include <array>

#include "../../include/HMI/UImg.h"

using namespace std;
class Sensor;
class Behavior;
class Milieu;
using Color = array<T, 3>;

class Bug {
private:
    // position variables
    int ID;
    Milieu* milieu;

    int x;
    int y;
    double orientation;
    // affichage
    double cumulX, cumulY;

    double currentVelocity;
    double normalVelocity;
    double fastVelocity;

    int age;
    int ageLimit;
    bool alive;

    double camouflageCapacity;
    double cloneProbability;
    double deathProbability;
    
    vector<Sensor*> sensors;
    Behavior* behavior;

public: // Forme canonique :
    static const double MAX_AGE;
    static const double MIN_AGE;
    static const double MAX_SIGHT;
    static const double MIN_SIGHT;
    static const double SIZE;
    static const double MAX_VELOCITY;
    static const double MIN_VELOCITY;
    static const double MAX_CLONE_PROB;
    static const double MAX_DEATH_PROB;
    static const double MIN_DEATH_PROB;
    static int NUM_BUGS;
    
    Bug(Milieu* milieu); // Constructeur par defaut
    Bug(const Bug& bug); // Constructeur de copies

    ~Bug();
    
    int getX() const { return x; }
    int getY() const { return y; }

    void action();
    void draw(UImg &support);
    bool isDetected(Bug* bug) const;
    void initLocation(int xLim, int yLim);
    
    void addSensor(Sensor* sensor);
    void setBehavior(Behavior* behavior);
    
    double getCamouflageCapacity() const;
    double getOrientation() const;
    void switchToFastVelocity();
    void switchToNormalVelocity();
    double getCurrentVelocity() const;
    
    void setOrientation(double orientation);
    void updateVelocity(double velocityFactor);
    void updateCamouflageCapacity(double camouflageCapacity);
    void updateDeathProbability(double deathProbFactor);

    bool isCollidingWith(Bug* bug) const;

    bool isAlive() const { return alive; }
    void kill();
    
private:
    void move();
    void clone();
};

#endif
