//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_SUICIDEBOOMER_H
#define PROJECTBE_SUICIDEBOOMER_H

#include "Behavior.h"

class Milieu;
class Bug;

class SuicideBoomer : public Behavior {
public:
    SuicideBoomer(Milieu* milieu, string name);
    ~SuicideBoomer() override;
    void updateParameters(Bug* bug) override;
    SuicideBoomer(const SuicideBoomer&) = delete;
    SuicideBoomer& operator=(const SuicideBoomer&) = delete;
    Color getColor() const override { return {255, 0, 0}; }
    virtual Behavior* clone() override;
};


#endif //PROJECTBE_SUICIDEBOOMER_H
