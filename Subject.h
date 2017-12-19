
// Subject-Observer design pattern
// Definition of Subject class, to be inherited from as an interface

#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include "Observer.h"

using std::set;

class Subject{
public:
    set<Observer*> observers;

    void addObserver(Observer* O);
    // the duty of a Subject is ONLY
    // to notify() every time something important happens
    // so that the Observer can update()
    void notify();
};

#endif // SUBJECT_H

