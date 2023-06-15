#ifndef _BUGFACTORY_H_
#define _BUGFACTORY_H_

#include <iostream>

using namespace std;
class Bug;
class Milieu;
class BehaviorFactory;
class SensorFactory;
class AccessoryFacade;

class BugFactory {
private :
    static BugFactory* bugFactory;
    
    BehaviorFactory* behaviorFactory;
    SensorFactory* sensorFactory;
    AccessoryFacade* accessoryFacade;
    
    Milieu* milieu;
    BugFactory(Milieu* milieu);

public:
    ~BugFactory();
    static BugFactory* getBugFactory(Milieu* milieu);
    Bug* getSuicideBoomer();
    Bug* getCareful();
    Bug* getSocial();
    Bug* getFearful();
    Bug* getMultiPersona();
    
    BugFactory(const BugFactory&) = delete;
    BugFactory& operator=(const BugFactory&) = delete;
};

#endif /* BugFactory_hpp */

