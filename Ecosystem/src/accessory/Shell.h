#ifndef _SHELL_H_
#define _SHELL_H_

#include "Accessory.h"

class Bug;

class Shell : public Accessory {
public:
    static double FACTOR_VELOCITY;
    static double FACTOR_DEATH;
    virtual void updateParameters(Bug* bug) const override;
};

#endif
