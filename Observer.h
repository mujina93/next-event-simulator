
// Subject-Observer design pattern
// Definition of Observer class, to be inherited from as an interface

#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer{
public:
    Subject* watched; // this observer can only watch one Subject!

    // the duty of an Observer is
    // 1) to start to watch() a subject at the beginning
    void watch(Subject* S);
    // 2) and to implement update()
    virtual void update() = 0; // do things when notified
};

#endif // OBSERVER_H

