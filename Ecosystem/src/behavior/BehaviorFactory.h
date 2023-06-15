#ifndef PROJECTBE_BEHAVIORFACTORY_H
#define PROJECTBE_BEHAVIORFACTORY_H

#include <map>
#include <string>

class Behavior;
class Milieu;
using namespace std;

class BehaviorFactory {
private:
    static BehaviorFactory* factory;
    static const string carefull;
    static const string fearful;
    static const string multipersona;
    static const string social;
    static const string suicideboomer;
    
    Milieu* milieu;

    std::map<string, Behavior*> behaviors;
    BehaviorFactory(Milieu* milieu);

public:
    ~BehaviorFactory();
    static BehaviorFactory* getBehaviorFactory(Milieu* milieu);
    Behavior* getMultiPersona();
    Behavior* getFearful();
    Behavior* getSocial();
    Behavior* getCareful();
    Behavior* getSuicideBoomer();

    BehaviorFactory(const BehaviorFactory&) = delete;
    BehaviorFactory& operator=(const BehaviorFactory&) = delete;
};


#endif //PROJECTBE_BEHAVIORFACTORY_H
