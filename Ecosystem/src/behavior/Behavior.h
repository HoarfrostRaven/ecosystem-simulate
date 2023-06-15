#ifndef _BEHAVIOR_H_
#define _BEHAVIOR_H_

#include "../../include/HMI/UImg.h"
#include <string>
#include <array>

using Color = std::array<T, 3>;
class Bug;
class Milieu;
using namespace std;

class Behavior {
protected:
    string name;
    Milieu* milieu;

public:
    virtual ~Behavior(){};
    virtual Color getColor() const = 0;
    virtual Behavior* clone() = 0;
    virtual void updateParameters(Bug* bug) = 0;
    string getBehaviorName() { return name; };
};


#endif //PROJECTBE_BEHAVIOR_H
