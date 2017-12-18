
// Subject-Observer design pattern
// Definition of Observer class, to be inherited from as an interface

#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer{
public:
    void watch(Subject* S);
    virtual void update() = 0; // do things when notified
};

#endif // OBSERVER_H

