
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
    void notify();
};

#endif // SUBJECT_H

