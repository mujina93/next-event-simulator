
// Subject-Observer design pattern
// Implementation of Subject class, to be inherited from as an interface

#include "Subject.h"
#include <set>

void Subject::addObserver(Observer* O){
    // add O to the list of observers (to be notified)
    observers.insert(O);
}

void Subject::notify(){
    // notifies the observers: let them update()
    typedef std::set<Observer*>::iterator soi;
    for(soi it=observers.begin(); it!=observers.end(); ++it){
        (*it)->update();
    }
}
