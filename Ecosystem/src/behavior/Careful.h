#ifndef PROJECTBE_CAREFUL_H
#define PROJECTBE_CAREFUL_H

#include "Behavior.h"
#include <string>

class Bug;
class Milieu;

class Careful : public Behavior {
public:
    Careful(Milieu* milieu, string name);
    ~Careful() override;
    void updateParameters(Bug* bug) override;
    Careful(const Careful&) = delete;
    Careful& operator=(const Careful&) = delete;
    Color getColor() const override { return {128, 0, 128}; }
    virtual Behavior* clone() override;
};


#endif //PROJECTBE_CAREFUL_H
