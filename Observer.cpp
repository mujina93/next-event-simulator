
// Subject-Observer design pattern
// Implementation of Observer class, to be inherited from as an interface

#include "Observer.h"
#include "Subject.h"

void Observer::watch(Subject* S){
    // register S so that when S notify(), the observer update()
    S->addObserver(this);
    // set S as something under control
    watched = S;
}
