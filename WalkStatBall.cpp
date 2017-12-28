
#include "DEBUG.h"
#include "GlobalTime.h"
#include "WalkStatBall.h"
#include <set>
#include <map>

WalkStatBall::WalkStatBall() :
    froms(), tos(), inside(), totalWalkTimes(0), firstTime(0){
}

void WalkStatBall::reset(){
    totalWalkTimes = 0;
    firstTime = clocktime;
}

void WalkStatBall::watchFrom(Station* S){
    froms.insert(S);
}

void WalkStatBall::watchTo(Station* S){
    tos.insert(S);
}

void WalkStatBall::noticeEvent(Event& ev){
    // a job is entering in the area of interest
    if(froms.find(ev.from) != froms.end()){
        // register the entering time
        inside[&ev] = clocktime;

        DER("@@ event entered at %lf\n",inside[&ev]);

        return;
    }
    // a job is going out from the area of interest
    if(tos.find(ev.to) != tos.end()){
        // walk time (time elapsed from enter to exit)
        double walk_time = clocktime - inside[&ev];
        // pops out the event
        inside.erase(&ev);
        // adds the new walk time to the total
        totalWalkTimes += walk_time;

        DER("@@ noticeing. TotalWalkTime = %lf\n",totalWalkTimes);

        return;
    }
    // nothing interesting
    return;
}

void WalkStatBall::update(){
    updateStat(totalWalkTimes, clocktime - firstTime);
    reset();

    DER("@@ regeneration hit. Updating WalkStatBall.\n");
}
