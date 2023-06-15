#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "Accessory.h"

class Bug;

class Camouflage : public Accessory {
public:
    static double FACTOR_CAMOUFLAGE_MIN;
    static double FACTOR_CAMOUFLAGE_MAX;
    virtual void updateParameters(Bug* bug) const override;
};

#endif
