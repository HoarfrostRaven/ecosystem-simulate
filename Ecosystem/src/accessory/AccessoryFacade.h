#ifndef _ACCESSORY_FACADE_H_
#define _ACCESSORY_FACADE_H_

#include <vector>

using namespace std;

class Accessory;
class Bug;

// Singleton Pattern
// Facade Pattern

class AccessoryFacade {
private:
    static AccessoryFacade* facade;
    vector<int> numAccessoryMax;
    vector<Accessory*> accessories;
    void addAccessory(Accessory* accessory, int num);
    
    AccessoryFacade();
    AccessoryFacade(const AccessoryFacade& accessoryFacade) = delete;
    AccessoryFacade& operator=(const AccessoryFacade& accessoryFacade) = delete;

public:
    ~AccessoryFacade();
    static AccessoryFacade* getAccessoryFacade();
    void attachAccessories(Bug* bug);
};

#endif
