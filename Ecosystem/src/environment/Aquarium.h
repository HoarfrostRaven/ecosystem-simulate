#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_

#include <CImg.h>

using namespace cimg_library;

class Milieu;
class BugFactory;

class Aquarium : public CImgDisplay {
private:
    Milieu* milieu;
    BugFactory* bugFactory;
    int delay;
public:
    Aquarium(int width, int length, int delay);
    ~Aquarium();
    Milieu* getMilieu() { return milieu; }
    void run();
    void addBug(int token);
    void reset();
};

#endif
