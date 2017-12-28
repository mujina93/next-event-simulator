
#include "DEBUG.h"
#include "StatNotifier.h"
#include "WalkStatBall.h"
#include "Events.h"

void StatNotifier::addStatObserver(WalkStatBall* O){
    // add O to the list of StatObservers (to be notified)
    StatObservers.insert(O);
}

void StatNotifier::notifyEvent(Event& ev){
    //DER("@@ notifying event...\n");
    // notifies the StatObservers: let them noticeEvent()
    typedef std::set<WalkStatBall*>::iterator soi;
    for(soi it=StatObservers.begin(); it!=StatObservers.end(); ++it){
        (*it)->noticeEvent(ev);
    }
}

void StatNotifier::notifyRegeneration(){
    //DER("@@ notifying regeneration!\n");
    // notifies the StatObservers: let them update()
    typedef std::set<WalkStatBall*>::iterator soi;
    for(soi it=StatObservers.begin(); it!=StatObservers.end(); ++it){
        (*it)->update();
    }
}
