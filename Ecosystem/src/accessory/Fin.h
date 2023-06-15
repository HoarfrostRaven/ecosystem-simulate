#ifndef _FIN_H_
#define _FIN_H_

#include "Accessory.h"

class Bug;

class Fin : public Accessory {
public:
    static double FACTOR_VELOCITY;
    virtual void updateParameters(Bug* bug) const override;
};

#endif
