#ifndef _EAR_H_
#define _EAR_H_

#include "Sensor.h"

class Bug;

class Ear : public Sensor {
public:
    static double DISTANCE_MIN;
    static double DISTANCE_MAX;
    static double DETECT_CAPACITY_MIN;
    static double DETECT_CAPACITY_MAX;
    
    Ear(Bug* owner);
    Ear(Bug* owner, double detectCapacity, double distance);
    virtual Sensor* clone(Bug* owner) const override;
    virtual void draw(UImg& support) const override;
    virtual bool isDetected(Bug* bug) const override;
};

#endif
