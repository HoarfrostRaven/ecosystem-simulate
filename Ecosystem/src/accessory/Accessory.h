#ifndef _ACCESSORY_H_
#define _ACCESSORY_H_

class Bug;

class Accessory {
public:
    virtual ~Accessory() {};
    virtual void updateParameters(Bug* bug) const = 0;
};

#endif
