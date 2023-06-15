#ifndef _EYE_H_
#define _EYE_H_

#include "Sensor.h"

class Bug;

class Eye : public Sensor {
public:
    static double ANGLE_MIN;
    static double ANGLE_MAX;
    static double DISTANCE_MIN;
    static double DISTANCE_MAX;
    static double DETECT_CAPACITY_MIN;
    static double DETECT_CAPACITY_MAX;
    
    Eye(Bug* owner);
    Eye(Bug* owner, double detectCapacity, double distance, double angle);
    virtual Sensor* clone(Bug* owner) const override;
    virtual void draw(UImg& support) const override;
    virtual bool isDetected(Bug* bug) const override;
};

#endif
