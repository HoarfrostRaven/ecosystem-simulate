//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_SOCIAL_H
#define PROJECTBE_SOCIAL_H

#include "Behavior.h"

class Milieu;
class Bug;

class Social : public Behavior {
public:
    Social(Milieu* milieu, string name);
    ~Social() override;
    void updateParameters(Bug* bug) override;
    Social(const Social&) = delete;
    Social& operator=(const Social&) = delete;
    Color getColor() const override { return {0, 255, 0}; }
    virtual Behavior* clone() override;
};


#endif //PROJECTBE_SOCIAL_H
