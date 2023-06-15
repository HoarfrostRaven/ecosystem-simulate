#include "Aquarium.h"
#include "Milieu.h"
#include "../bug/BugFactory.h"
#include "../../include/Random.h"
#include <iostream>

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;
using namespace std;

Aquarium::Aquarium(int width, int height, int _delay) : CImgDisplay(), delay(_delay) {
    int screenWidth = 1280; //screen_width();
    int screenHeight = 1024; //screen_height();
    
    cout << "const Aquarium" << endl;

    milieu = new Milieu(width, height);
    assign(*milieu, "Simulation d'ecosysteme");
    
    bugFactory = BugFactory::getBugFactory(milieu);

    move(static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2));
}

Aquarium::~Aquarium() {
    cout << "Destruct Aquarium" << endl;
    delete milieu;
    delete bugFactory;
}

void Aquarium::addBug(int token){
    if(token == 0) {
        token = Random::get(1, 5);
    }
    
    switch(token) {
        case 1:
            milieu->addBug(bugFactory->getMultiPersona());
            break;
        case 2:
            milieu->addBug(bugFactory->getFearful());
            break;
        case 3:
            milieu->addBug(bugFactory->getSuicideBoomer());
            break;
        case 4:
            milieu->addBug(bugFactory->getSocial());
            break;
        case 5:
            milieu->addBug(bugFactory->getCareful());
            break;
    }
}

void Aquarium::run() {
    cout << "running Aquarium" << endl;

    while (!is_closed()) {
        if ( is_key() ) {
            cout << "You have pressed the key " << static_cast<unsigned char>( key() );
            cout << " (" << key() << ")" << endl;
            
            if (is_keyESC()) {
                reset();
                close();
            } else if (is_keyA()) {
                addBug(0);
            } else if (is_key1()) {
                addBug(1);
            } else if (is_key2()) {
                addBug(2);
            } else if (is_key3()) {
                addBug(3);
            } else if (is_key4()) {
                addBug(4);
            } else if (is_key5()) {
                addBug(5);
            } else if (is_keyK()) {
                milieu->kill();
            }
        }

        milieu->step();
        display(*milieu);

        wait(delay);
    }
    reset();
}

void Aquarium::reset() {
    milieu->resetAnalyseResult();
}
