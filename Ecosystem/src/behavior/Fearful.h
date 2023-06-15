//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_FEARFUL_H
#define PROJECTBE_FEARFUL_H

#include "Behavior.h"
#include <string>

using namespace std;
class Bug;
class Milieu;

class Fearful : public Behavior {
public:
    Fearful(Milieu* milieu, string name);
    ~Fearful() override;
    void updateParameters(Bug* bug) override;
    Fearful(const Fearful&) = delete;
    Fearful& operator=(const Fearful&) = delete;
    Color getColor() const override { return {0, 0, 255}; }
    virtual Behavior* clone() override;
};


#endif //PROJECTBE_FEARFUL_H
