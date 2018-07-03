
#include "DEBUG.h"
#include "StatNotifier.h"
#include "WalkStat.h"
#include "Events.h"

void StatNotifier::addStatObserver(WalkStat* O){
    // add O to the list of StatObservers (to be notified)
    StatObservers.insert(O);
}

void StatNotifier::unsubscribeFromAll(){
    StatObservers.clear();
}

void StatNotifier::notifyEvent(Event& ev){
    //DER("@@ notifying event...\n");

    // notifies the StatObservers: let them noticeEvent()
    typedef std::set<WalkStat*>::iterator soi;
    for(soi it=StatObservers.begin(); it!=StatObservers.end(); ++it){
        (*it)->noticeEvent(ev);
    }
}

void StatNotifier::notifyRegeneration(){
    //DER("@@ notifying regeneration!\n");

    // notifies the StatObservers: let them update()
    typedef std::set<WalkStat*>::iterator soi;
    for(soi it=StatObservers.begin(); it!=StatObservers.end(); ++it){
        (*it)->update();
    }
}
