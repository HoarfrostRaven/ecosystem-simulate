#include "AccessoryFacade.h"
#include "Accessory.h"
#include "Camouflage.h"
#include "Shell.h"
#include "Fin.h"
#include "../bug/Bug.h"
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;
using namespace std;

AccessoryFacade* AccessoryFacade::facade = nullptr;

AccessoryFacade::AccessoryFacade(){
    vector<int> numAccessoryMax;
    vector<Accessory*> accessories;
    
    addAccessory(new Camouflage(), 1);
    addAccessory(new Shell(), 1);
    addAccessory(new Fin(), 2);
}

AccessoryFacade::~AccessoryFacade() {
    for (auto accessory : accessories) {
        delete accessory;
    }
    facade = nullptr;
}

AccessoryFacade* AccessoryFacade::getAccessoryFacade() {
    if(facade == nullptr) {
        facade = new AccessoryFacade();
    }
    return facade;
}

// Each type of accessory has a maximum number of installations
void AccessoryFacade::addAccessory(Accessory* accessory, int num) {
    numAccessoryMax.push_back(num);
    accessories.push_back(accessory);
}

// Installation is carried out according to the maximum number of installations for each accessory
void AccessoryFacade::attachAccessories(Bug* bug) {
    int numAccessories = accessories.size();
    for (int i = 0; i < numAccessories; i++) {
        int randomNum = Random::get(0, numAccessoryMax[i]);
        for (int j = 0; j < randomNum; j++) {
            accessories[i]->updateParameters(bug);
        }
    }
}
