
#ifndef STATNOTIFIER_H
#define STATNOTIFIER_H

#include <set>
#include "WalkStat.h"
#include "Events.h"

using std::set;

class StatNotifier{
public:
    set<WalkStat*> StatObservers;

    void addStatObserver(WalkStat* O);
    void unsubscribeFromAll();
    // the duty of a Subject/Notifier is ONLY
    // to notify() every time something important happens
    // so that the Observer can update()
    void notifyEvent(Event& ev);
    void notifyRegeneration();
};

#endif // STATNOTIFIER_H

