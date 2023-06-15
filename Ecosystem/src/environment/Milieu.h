#ifndef _MILIEU_H_
#define _MILIEU_H_

#include "UImg.h"
#include "../constants.h"
#include <vector>

class Bug;

class Milieu : public UImg
{

private :
    static const T white[];
    int width, height;
    std::vector<Bug*> listBugs;
public:
    static int NUM_BUG;
    static int NUM_COLLISION;
    static int NUM_CLONE;
    static int NUM_DEATH_BY_COLLISION;
    static int NUM_DEATH_BY_KILL;
    static int NUM_DEATH_BY_AGE;
    static int NUM_CAREFUL;
    static int NUM_FEARFUL;
    static int NUM_MULTI_PERSONA;
    static int NUM_SOCIAL;
    static int NUM_SUCIDE_BOOMER;
    
    Milieu(int _width, int _height);
    ~Milieu();
    void step();
    void addBug(Bug* bug);
    void removeBug(Bug* bug);
    std::vector<Bug*> getNeighbors(Bug* bug);
    std::vector<Bug*> getBugs();
    int getNumNeighbors(Bug* bug);
    int getWidth() const { return width; }
    int getHeight() const { return height - INFO_BAR_HEIGHT; }
    void kill();
    void showAnalyseResult();
    void resetAnalyseResult();
};


#endif
