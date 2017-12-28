
#ifndef STATNOTIFIER_H
#define STATNOTIFIER_H

#include <set>
#include "WalkStatBall.h"
#include "Events.h"

using std::set;

class StatNotifier{
public:
    set<WalkStatBall*> StatObservers;

    void addStatObserver(WalkStatBall* O);
    // the duty of a Subject/Notifier is ONLY
    // to notify() every time something important happens
    // so that the Observer can update()
    void notifyEvent(Event& ev);
    void notifyRegeneration();
};

#endif // STATNOTIFIER_H

